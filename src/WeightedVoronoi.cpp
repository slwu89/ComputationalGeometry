// ////////////////////////////////////////////////////
// //
// // Sean Wu
// // Weighted Voronoi Diagram source file
// // June 25, 2017
// //
// ////////////////////////////////////////////////////
//
// // #include "WeightedVoronoi.hpp"
//
// #include <Rcpp.h>
//
// // construction kernel
// #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <CGAL/convex_hull_2.h>
// #include <CGAL/MP_Float.h>
//
// // Delunay triangulation; dual of graph is a Voronoi diagram
// #include <CGAL/Delaunay_triangulation_2.h>
// #include <CGAL/Voronoi_diagram_2.h>
//
// // Apollonius graph is the dual of the additively weighted Voronoi diagram
// #include <CGAL/Apollonius_graph_2.h>
// #include <CGAL/Apollonius_graph_traits_2.h>
// #include <CGAL/Apollonius_graph_adaptation_traits_2.h>
// #include <CGAL/Apollonius_graph_adaptation_policies_2.h>
//
// // typedefs
//
//
//
// // kernel
// typedef CGAL::Exact_predicates_inexact_constructions_kernel     KernelExact;
//
// // graph
// typedef CGAL::Apollonius_graph_traits_2<KernelExact>            ApolloniusGraph_Traits;
// typedef CGAL::Apollonius_site_2<KernelExact>                    ApolloniusGraph_Site2;
// typedef CGAL::Apollonius_graph_2<ApolloniusGraph_Traits>        ApolloniusGraph;
//
// typedef CGAL::Apollonius_graph_adaptation_traits_2<ApolloniusGraph>                     ApolloniusGraph_AdaptTraits;
// typedef CGAL::Apollonius_graph_caching_degeneracy_removal_policy_2<ApolloniusGraph>     ApolloniusGraph_RemovePolicy;
// typedef CGAL::Voronoi_diagram_2<ApolloniusGraph,ApolloniusGraph_AdaptTraits,ApolloniusGraph_RemovePolicy>  ApolloniusGraph_VoronoiDiagram;
//
// // site
// typedef ApolloniusGraph_Site2::Point_2                            Site2_Point2;
// typedef ApolloniusGraph_Site2::Weight                             Site2_Weight;
//
// // data extraction
// typedef ApolloniusGraph_VoronoiDiagram::Locate_result             Locate_result;
// typedef ApolloniusGraph_VoronoiDiagram::Vertex_handle             Vertex_handle;
// typedef ApolloniusGraph_VoronoiDiagram::Face_handle               Face_handle;
// typedef ApolloniusGraph_VoronoiDiagram::Halfedge_handle           Halfedge_handle;
// typedef ApolloniusGraph_VoronoiDiagram::Ccb_halfedge_circulator   Ccb_halfedge_circulator;
//
//
// // using namespace Rcpp;
//
// //' Weighted Voronoi Diagram
// //'
// //' Write some docs here
// //'
// //' @export
// // [[Rcpp::export]]
// Rcpp::List WeightedVoronoi(const Rcpp::NumericVector &coordX, const Rcpp::NumericVector &coordY, const Rcpp::NumericVector &Weights){
//
//   if((coordX.size()!=coordY.size()) || (coordY.size()!=Weights.size())){
//     Rcpp::stop("all input vectors must be of same length");
//   }
//
//   // generate list of weighted nodes
//   std::vector<ApolloniusGraph_Site2> Nodes;
//
//   for(int ix=0; ix<coordX.size(); ix++){
//     Nodes.push_back(ApolloniusGraph_Site2(Site2_Point2(coordX.at(ix)), Site2_Point2(coordX.at(ix)), Site2_Weight(Weights.at(ix))));
//   }
//
//   // generate Voronoi diagram
//   ApolloniusGraph_VoronoiDiagram Voronoi;
//   Voronoi.clear();
//   Voronoi.insert(Nodes.begin(),Nodes.end()); // insert nodes
//
//   // extract polygons from Voronoi diagram
//   std::vector<double> voronoiX;
//   std::vector<double> voronoiY;
//
//   ApolloniusGraph_VoronoiDiagram::Bounded_faces_iterator faces_iterator;
//   for(faces_iterator = Voronoi.bounded_faces_begin(); faces_iterator != Voronoi.bounded_faces_end(); faces_iterator++){
//
//     Ccb_halfedge_circulator ec_start = (faces_iterator)->ccb();
//     Ccb_halfedge_circulator ec = ec_start;
//
//     do {
//         double x = ((Halfedge_handle)ec)->source()->point().x();
//         double y = ((Halfedge_handle)ec)->source()->point().y();
//         voronoiX.push_back(x);
//         voronoiY.push_back(y);
//     } while ( ++ec != ec_start );
//
//   }
//
//   return(
//     Rcpp::List::create(
//       Rcpp::Named("x")=voronoiX,
//       Rcpp::Named("y")=voronoiY
//     )
//   );
// }
