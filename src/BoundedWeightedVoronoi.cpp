////////////////////////////////////////////////////
//
// Sean Wu & Yuji Saikai
// Bounded Weighted Voronoi Diagram
// July 1, 2017
//
////////////////////////////////////////////////////

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


// stuff to take voronoi -> delunay -> crop it and output.

#include <CGAL/Delaunay_triangulation_2.h>
#include <iterator>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Segment_2 Segment_2;
typedef K::Ray_2 Ray_2;
typedef K::Line_2 Line_2;
typedef CGAL::Delaunay_triangulation_2<KernelExact> Delaunay_triangulation_2;

//A class to recover Voronoi diagram from stream.
//Rays, lines and segments are cropped to a rectangle
//so that only segments are stored
struct Cropped_voronoi_from_delaunay{
  std::list<Segment_2> m_cropped_vd;
  Iso_rectangle_2 m_bbox;
  Cropped_voronoi_from_delaunay(const Iso_rectangle_2& bbox):m_bbox(bbox){}
  template <class RSL>
  void crop_and_extract_segment(const RSL& rsl){
    CGAL::Object obj = CGAL::intersection(rsl,m_bbox);
    const Segment_2* s=CGAL::object_cast<Segment_2>(&obj);
    if (s) m_cropped_vd.push_back(*s);
  }
  void operator<<(const Ray_2& ray) { crop_and_extract_segment(ray); }
  void operator<<(const Line_2& line) { crop_and_extract_segment(line); }
  void operator<<(const Segment_2& seg){ crop_and_extract_segment(seg); }
};


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
Rcpp::List BoundedWeightedVoronoi(
  const Rcpp::NumericVector &coordX,
  const Rcpp::NumericVector &coordY,
  const Rcpp::NumericVector &Weights,
  const double &minX,
  const double &minY,
  const double &maxX,
  const double &maxY
){

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

  Iso_rectangle_2 bbox(minX,minY,maxX,maxY);
  Cropped_voronoi_from_delaunay vor(bbox);

  Voronoi.dual().draw_dual(vor);

  int size = vor.m_cropped_vd.size();
  // get the segments out
  std::vector<Segment_2> segmentOut(size);
  std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),
            segmentOut.begin());
  // std::vector<Rcpp::NumericVector> segmentToR;
  std::vector<std::vector<double>> segmentToR;
  std::vector<double> thisSegment(4);
  for(auto it = segmentOut.begin(); it != segmentOut.end(); it++){

    thisSegment.clear();
    thisSegment.push_back(it->point(0).x());
    thisSegment.push_back(it->point(0).y());
    thisSegment.push_back(it->point(1).x());
    thisSegment.push_back(it->point(1).y());
    segmentToR.push_back(thisSegment);

  }

  return(
    Rcpp::List::create(
      Rcpp::Named("segments")=segmentToR
    )
  );

}
