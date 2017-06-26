////////////////////////////////////////////////////
//
// Sean Wu
// Weighted Voronoi Diagram source file
// June 25, 2017
//
////////////////////////////////////////////////////

#include "WeightedVoronoi.hpp"


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
