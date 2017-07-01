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

  int xx = Voronoi.number_of_faces();
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

  return(
    Rcpp::List::create(
      Rcpp::Named("x")=PolygonX,
      Rcpp::Named("y")=PolygonY
    )
  );
}
