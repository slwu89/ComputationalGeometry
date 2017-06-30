////////////////////////////////////////////////////
//
// Sean Wu
// Weighted Voronoi Diagram source file
// June 25, 2017
//
////////////////////////////////////////////////////

// #include "WeightedVoronoi.hpp"

#include <Rcpp.h>

// construction kernel
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/MP_Float.h>

// Delunay triangulation; dual of graph is a Voronoi diagram
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>

// Apollonius graph is the dual of the additively weighted Voronoi diagram
#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Apollonius_graph_traits_2.h>
#include <CGAL/Apollonius_graph_adaptation_traits_2.h>
#include <CGAL/Apollonius_graph_adaptation_policies_2.h>

// typedefs

// kernel
typedef CGAL::Exact_predicates_inexact_constructions_kernel     KernelExact;

// graph
typedef CGAL::Apollonius_graph_traits_2<KernelExact>            ApolloniusGraph_Traits;
typedef CGAL::Apollonius_site_2<KernelExact>                    ApolloniusGraph_Site2;
typedef CGAL::Apollonius_graph_2<ApolloniusGraph_Traits>        ApolloniusGraph;

typedef CGAL::Apollonius_graph_adaptation_traits_2<ApolloniusGraph>                     ApolloniusGraph_AdaptTraits;
typedef CGAL::Apollonius_graph_caching_degeneracy_removal_policy_2<ApolloniusGraph>     ApolloniusGraph_RemovePolicy;
typedef CGAL::Voronoi_diagram_2<ApolloniusGraph,ApolloniusGraph_AdaptTraits,ApolloniusGraph_RemovePolicy>  ApolloniusGraph_VoronoiDiagram;

// site
typedef ApolloniusGraph_Site2::Point_2                            Site2_Point2;
typedef ApolloniusGraph_Site2::Weight                             Site2_Weight;

// data extraction
typedef ApolloniusGraph_VoronoiDiagram::Locate_result             Locate_result;
typedef ApolloniusGraph_VoronoiDiagram::Vertex_handle             Vertex_handle;
typedef ApolloniusGraph_VoronoiDiagram::Face_handle               Face_handle;
typedef ApolloniusGraph_VoronoiDiagram::Face                      Face;
typedef ApolloniusGraph_VoronoiDiagram::Halfedge_handle           Halfedge_handle;
typedef ApolloniusGraph_VoronoiDiagram::Halfedge                  Halfedge;
typedef ApolloniusGraph_VoronoiDiagram::Face_iterator             Face_iterator;
typedef ApolloniusGraph_VoronoiDiagram::Ccb_halfedge_circulator   Ccb_halfedge_circulator;

typedef std::vector<double>             vectorDouble;
typedef std::vector<vectorDouble>       vectorPolygon;

//' Weighted Voronoi Diagram
//'
//' Produce a weighted Voronoi diagram. This is a wrapper for the CGAL library, see \url{http://doc.cgal.org/latest/Apollonius_graph_2/index.html} for algorithm details.
//'
//' @param coordX numeric vector of x coordinates
//' @param coordY numeric vector of y coordinates
//' @param Weights numeric vector of weights
//'
//' @export
// [[Rcpp::export]]
Rcpp::List WeightedVoronoi(const Rcpp::NumericVector &coordX, const Rcpp::NumericVector &coordY, const Rcpp::NumericVector &Weights){

  if((coordX.size()!=coordY.size()) || (coordY.size()!=Weights.size())){
    Rcpp::stop("all input vectors must be of same length");
  }

  // generate list of weighted nodes
  std::vector<ApolloniusGraph_Site2> Nodes;

  for(int ix=0; ix<coordX.size(); ix++){
    Nodes.push_back(ApolloniusGraph_Site2(Site2_Point2(double(coordX.at(ix)),double(coordY.at(ix))),Site2_Weight(double(Weights.at(ix)))));
  }

  // generate Voronoi diagram
  ApolloniusGraph_VoronoiDiagram Voronoi;
  Voronoi.clear();
  Voronoi.insert(Nodes.begin(),Nodes.end()); // insert nodes

  double xx = Voronoi.number_of_faces();
  Rcpp::Rcout << "made VDA object with faces: " << xx << std::endl;


  // extract polygons from Voronoi diagram
  ApolloniusGraph_VoronoiDiagram::Bounded_faces_iterator faces_iterator;

  vectorDouble faceX;
  vectorDouble faceY;

  vectorPolygon PolygonX;
  vectorPolygon PolygonY;

  for(faces_iterator = Voronoi.bounded_faces_begin(); faces_iterator != Voronoi.bounded_faces_end(); faces_iterator++){

    faceX.clear();
    faceY.clear();

    Ccb_halfedge_circulator ec_start = (faces_iterator)->ccb();
    Ccb_halfedge_circulator ec = ec_start;

    do {
        double x = ((Halfedge_handle)ec)->source()->point().x();
        double y = ((Halfedge_handle)ec)->source()->point().y();
        faceX.push_back(x);
        faceY.push_back(y);
    } while ( ++ec != ec_start );

    PolygonX.push_back(faceX);
    PolygonY.push_back(faceY);

  }


  // hyperbola origin and targets
  std::vector<Rcpp::List> hyperbolaSources;
  std::vector<Rcpp::List> hyperbolaTargets;

  // To prevent edges from being considered from both sides, we collect the
  // already visited ones in a set.
  std::set<Halfedge> edges;
  Halfedge currHalfedge, currOppositeHalfedge;
  // the two sites adjacent to a halfedge
  ApolloniusGraph_Site2 origin, neighbor;
  // the two endpoints of a halfedge
  Site2_Point2 source, target;

  int numEdges = 0;
  int numHalfedges = 0;

  for (Face_iterator face_it = Voronoi.faces_begin();
    face_it != Voronoi.faces_end(); face_it++) {
    Face currFace = *face_it;
    origin = currFace.dual()->site();

    Ccb_halfedge_circulator edge_ci, edge_ci_end;
    edge_ci = edge_ci_end = currFace.ccb();
    do {
      numHalfedges++;
      currHalfedge = *edge_ci;
      currOppositeHalfedge = *currHalfedge.opposite();
      // the current edge hasn't been visited yet
      if (edges.find(currOppositeHalfedge) == edges.end()) {
        numEdges++;

        neighbor = currOppositeHalfedge.face()->dual()->site();

        if (!currHalfedge.has_source() || !currHalfedge.has_target()) {
          continue;
        }

        // fprintf(intersectionsFile, "%.30f %.30f %.30f %.30f %.30f %.30f ",
        //   origin.point().x(), origin.point().y(), origin.weight(),
        //   neighbor.point().x(), neighbor.point().y(), neighbor.weight());

        Rcpp::List hyperbolaSource;

        // the first endpoint of the hyperbola
        if (currHalfedge.has_source()) {
          source = (*currHalfedge.source()).point();
          hyperbolaSource = Rcpp::List::create(Rcpp::Named("sourceX") = source.x(), Rcpp::Named("sourceY") = source.y());
        } else {
          hyperbolaSource = Rcpp::List::create(Rcpp::Named("sourceX") = R_NilValue, Rcpp::Named("sourceY") = R_NilValue);
        }

        hyperbolaSources.push_back(hyperbolaSource);

        Rcpp::List hyperbolaTarget;

        // the second endpoint of the hyperbola
        if (currHalfedge.has_target()) {
          target = (*currHalfedge.target()).point();
          hyperbolaTarget = Rcpp::List::create(Rcpp::Named("targetX") = target.x(), Rcpp::Named("targetY") = target.y());
        } else {
          hyperbolaTarget = Rcpp::List::create(Rcpp::Named("targetX") = R_NilValue, Rcpp::Named("targetY") = R_NilValue);
        }

        hyperbolaTargets.push_back(hyperbolaTarget);

      }
      edges.insert(currHalfedge);
    } while(++edge_ci != edge_ci_end);
  }




  return(
    Rcpp::List::create(
      Rcpp::Named("x")=PolygonX,
      Rcpp::Named("y")=PolygonY,
      Rcpp::Named("hyperbolaSources") = hyperbolaSources,
      Rcpp::Named("hyperbolaTargets") = hyperbolaTargets
    )
  );
}
