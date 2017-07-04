////////////////////////////////////////////////////
//
// Sean Wu & Yuji Saikai
// Bounded Weighted Voronoi Diagram
// July 4, 2017
//
////////////////////////////////////////////////////

// #include <stdio.h>
// #include <iostream>
// #include <fstream>
// #include <cassert>
// #include <iterator>

#include <Rcpp.h>

// the number type
#include <CGAL/MP_Float.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Segment_2 Segment_2;
typedef K::Ray_2 Ray_2;
typedef K::Line_2 Line_2;

// typedefs for the traits and the algorithm
#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Apollonius_graph_traits_2.h>

typedef CGAL::Apollonius_graph_traits_2<K>   Traits;
typedef CGAL::Apollonius_graph_2<Traits>     Apollonius_graph;
typedef CGAL::Apollonius_site_2<K>           Site_2;
typedef Site_2::Point_2                      Apollonius_Point_2;
typedef Site_2::Weight                       Apollonius_Weight;

// output containers
typedef std::vector<double> vertex; // hold vertex
typedef std::vector<vertex> allVertices; // hold all vertices
typedef std::vector<Segment_2> Segment_2_Vector; // hold all segments
typedef std::vector<double> segment;
typedef std::vector<segment> allSegments;
typedef std::vector<allSegments> SegmentsByVertexToR;


//A class to recover Voronoi diagram from stream.
struct Cropped_voronoi_from_apollonius{
    std::list<Segment_2> m_cropped_vd;
    Iso_rectangle_2 m_bbox;

    Cropped_voronoi_from_apollonius(const Iso_rectangle_2& bbox):m_bbox(bbox){}

    template <class RSL>
    void crop_and_extract_segment(const RSL& rsl){
        CGAL::Object obj = CGAL::intersection(rsl,m_bbox);
        const Segment_2* s=CGAL::object_cast<Segment_2>(&obj);
        if (s) m_cropped_vd.push_back(*s);
    }

    void operator<<(const Ray_2& ray)    { crop_and_extract_segment(ray); }
    void operator<<(const Line_2& line)  { crop_and_extract_segment(line); }
    void operator<<(const Segment_2& seg){ crop_and_extract_segment(seg); }

    void reset() {
        m_cropped_vd.erase(m_cropped_vd.begin(), m_cropped_vd.end());
    }
};

//' Voronoi Treemap Algorithm
//'
//' See \url{https://www.stat.auckland.ac.nz/~paul/Reports/VoronoiTreemap/voronoiTreeMap.html} for algorithm details.
//'
//' @param coordX numeric vector of x coordinates
//' @param coordY numeric vector of y coordinates
//' @param Weights numeric vector of weights
//'
//' @export
// [[Rcpp::export]]
Rcpp::List voronoiTreemap(
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

  Apollonius_graph ApolloniusGraph;

  for(int i=0; i<coordX.size(); i++){
    ApolloniusGraph.insert(
      Site_2(Apollonius_Point_2(coordX.at(i),coordY.at(i)),
             Apollonius_Weight(Weights.at(i))
      )
    );
  }

  //construct a rectangle
  // This is set up to be well outside the range of the sites
  // This means that we should be able to just join up the end
  // points for any open cells, without fear of crossing the
  // area that contains the sites (EXCEPT for pretty pathological
  // cases, e.g., where there are only two sites)
  Iso_rectangle_2 bbox(minX,minY,maxX,maxY);

  Cropped_voronoi_from_apollonius vor(bbox);

  // initalize output containers
  vertex vertexContainer;
  allVertices verticesContainer;
  Segment_2_Vector segment_2_Container;
  segment segmentContainer;
  allSegments segmentsContainer;
  SegmentsByVertexToR allSegmentsContainer;

  Rcpp::Rcout << "i am ready to extract Voronoi edges" << std::endl;

  // iterate to extract Voronoi diagram edges around each vertex
  Apollonius_graph::Finite_vertices_iterator vit;
  for (vit = ApolloniusGraph.finite_vertices_begin();
       vit != ApolloniusGraph.finite_vertices_end();
       ++vit) {

      vertexContainer.clear();
      vertexContainer.push_back(vit->site().point().x());
      vertexContainer.push_back(vit->site().point().y());
      verticesContainer.push_back(vertexContainer);
      // Rcpp::Rcout << "Vertex ";
      // Rcpp::Rcout << vit->site().point();
      // Rcpp::Rcout << std::endl;

      Apollonius_graph::Edge_circulator ec = ApolloniusGraph.incident_edges(vit), done(ec);
      if (ec != 0) {
          do {
              ApolloniusGraph.draw_dual_edge(*ec, vor);
          } while(++ec != done);
      }
      // print the cropped Voronoi diagram edges as segments
      int size = vor.m_cropped_vd.size();
      std::vector<Segment_2> segment_2_Container(size);
      std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),segment_2_Container.begin());
      // segment_2_Container.clear();
      // std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),
      //           std::ostream_iterator<Segment_2>(std::cout,"\n"));

      // fill up segmentsContainer
      segmentsContainer.clear();
      for(auto it = segment_2_Container.begin(); it != segment_2_Container.end(); it++){

        segmentContainer.clear();
        segmentContainer.push_back(it->point(0).x());
        segmentContainer.push_back(it->point(0).y());
        segmentContainer.push_back(it->point(1).x());
        segmentContainer.push_back(it->point(1).y());
        segmentsContainer.push_back(segmentContainer);

      }

      // put in outermost segment holder thingy.
      allSegmentsContainer.push_back(segmentsContainer);

  }

  //extract the entire cropped Voronoi diagram
  // ApolloniusGraph.draw_dual(vor);

  vor.reset();
  Rcpp::Rcout << "i am ready to dump output" << std::endl;

  return(
    Rcpp::List::create(
      Rcpp::Named("debug")=1,
      Rcpp::Named("vertices")=verticesContainer,
      Rcpp::Named("segments")=segmentsContainer
    )
  );
}
