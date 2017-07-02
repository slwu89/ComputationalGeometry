////////////////////////////////////////////////////
//
// Sean Wu & Yuji Saikai
// Bounded Voronoi Diagram
// July 1, 2017
//
////////////////////////////////////////////////////


#include <Rcpp.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iterator>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Segment_2 Segment_2;
typedef K::Ray_2 Ray_2;
typedef K::Line_2 Line_2;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay_triangulation_2;

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


//' Bounded Weighted Voronoi Diagram
//'
//' Produce a weighted and bounded Voronoi diagram. This is a wrapper for the CGAL library, see \url{http://doc.cgal.org/latest/Apollonius_graph_2/index.html} for algorithm details.
//'
//' @param coordX numeric vector of x coordinates
//' @param coordY numeric vector of y coordinates
//' @param Weights numeric vector of weights
//' @param minX coordinates of bounding rectangle
//' @param minY coordinates of bounding rectangle
//' @param maxX coordinates of bounding rectangle
//' @param maxY coordinates of bounding rectangle
//'
//' @export
// [[Rcpp::export]]
Rcpp::List BoundedUnweightedVoronoi(
  const Rcpp::NumericVector &coordX,
  const Rcpp::NumericVector &coordY,
  const double &minX,
  const double &minY,
  const double &maxX,
  const double &maxY
){

  std::vector<Point_2> points;

  for(int ix=0; ix<coordX.size(); ix++){
    points.push_back(Point_2(coordX.at(ix),coordY.at(ix)));
  }

  Delaunay_triangulation_2 dt2;
  //insert points into the triangulation
  dt2.insert(points.begin(),points.end());
  //construct a rectangle
  Iso_rectangle_2 bbox(minX,minY,maxX,maxY);
  Cropped_voronoi_from_delaunay vor(bbox);
  //extract the cropped Voronoi diagram
  dt2.draw_dual(vor);

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

  return(Rcpp::List::create(
    Rcpp::Named("segments")=segmentToR
  ));
}
