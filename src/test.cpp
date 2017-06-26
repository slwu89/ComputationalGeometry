// //
// //  main.cpp
// //  cgalTest
// //
// //  Created by Sean Wu on 6/24/17.
// //  Copyright © 2017 Sean Wu. All rights reserved.
// //
//
// // header files
//
// // for pointsAndSegment
// #include <stdio.h>
// #include <iostream>
// #include <vector>
// #include <sstream>
// #include <random>
// #include <Rcpp.h>
//
// #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <CGAL/convex_hull_2.h>
//
// #include <CGAL/MP_Float.h>
// #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
// #include <CGAL/Delaunay_triangulation_2.h>
//
// #include <CGAL/Apollonius_graph_2.h>
// #include <CGAL/Apollonius_graph_traits_2.h>
// #include <CGAL/Apollonius_graph_adaptation_traits_2.h>
// #include <CGAL/Apollonius_graph_adaptation_policies_2.h>
//
// #include <CGAL/Voronoi_diagram_2.h>
//
// // get data out
//
//
// typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel_Exact;
// // typedef CGAL::Apollonius_graph_traits_2<Kernel_Exact>             APT;
// typedef CGAL::Apollonius_site_2<Kernel_Exact>                   Site_2_Apo;
// typedef Site_2_Apo::Point_2                                     Site_2_Point_2;
// typedef Site_2_Apo::Weight                                      Site_2_Weight;
//
// typedef CGAL::Apollonius_graph_traits_2<Kernel_Exact>                              AGT2_K;
// typedef CGAL::Apollonius_graph_2<AGT2_K>                                            AG2;
// typedef CGAL::Apollonius_graph_adaptation_traits_2<AG2>                            AG2_Trait;
// typedef CGAL::Apollonius_graph_caching_degeneracy_removal_policy_2<AG2>            AG2_Policy;
// typedef CGAL::Voronoi_diagram_2<AG2,AG2_Trait,AG2_Policy>                          VD_AG2;
//
// // typedefs to get data out
// typedef VD_AG2::Locate_result             Locate_result;
// typedef VD_AG2::Vertex_handle             Vertex_handle;
// typedef VD_AG2::Face_handle               Face_handle;
// typedef VD_AG2::Halfedge_handle           Halfedge_handle;
// typedef VD_AG2::Ccb_halfedge_circulator   Ccb_halfedge_circulator;
//
//
//
// std::random_device seed;  //Will be used to obtain a seed for the random number engine
// std::mt19937 RNG(seed()); //Standard mersenne_twister_engine seeded with rd()
//
// std::uniform_real_distribution<> randomPoint(0, 30);
// std::uniform_real_distribution<> randomWeight(0, 50);
//
//
// //' @export
// // [[Rcpp::export]]
// Rcpp::List WeightedVoronoiTest(const Rcpp::NumericVector &inputX, const Rcpp::NumericVector &inputY, const Rcpp::NumericVector &Weights){
//
//     Rcpp::Rcout << "got here 1" << std::endl;
//     std::vector<Site_2_Apo> List_Nodes;
//
//     // for(int i = 0; i<= 20; i++){
//     //     for(int j = 0; j <= 20;j++)
//     //     {
//     //         List_Nodes.push_back(Site_2_Apo(Site_2_Point_2(i+randomPoint(RNG),j+randomPoint(RNG)),Site_2_Weight(randomWeight(RNG))));
//     //     }
//     // }
//
//     for(int i = 0; i< inputX.size(); i++){
//       List_Nodes.push_back(Site_2_Apo(Site_2_Point_2(double(inputX(i)),double(inputY(i))),Site_2_Weight(double(Weights(i)))));
//     }
//
//     VD_AG2 VDA;      //Voronoi Apol
//
//     Rcpp::Rcout << "got here 2 " << std::endl;
//     ///Voronoi Generation
//     VDA.clear();
//     VDA.insert(List_Nodes.begin(),List_Nodes.end());
//     double xx = VDA.number_of_faces();
//
//     Rcpp::Rcout << "made VDA object with faces: " << xx << std::endl;
//
// //    VDA.bounded_faces_iterator f;
//     VD_AG2::Bounded_faces_iterator f;
//
//
//    typedef std::vector<double> vectorDouble;
//
//    vectorDouble coordX;
//    vectorDouble coordY;
//
//     std::vector<vectorDouble> PolygonX;
//     std::vector<vectorDouble> PolygonY;
//     for(f = VDA.bounded_faces_begin(); f != VDA.bounded_faces_end(); f++)
//     {
//
//         Rcpp::Rcout << "iterating..." << std::endl;
//         coordX.clear();
//         coordY.clear();
//         Ccb_halfedge_circulator ec_start = (f)->ccb();
//         Ccb_halfedge_circulator ec = ec_start;
//         do {
//             double x = ((Halfedge_handle)ec)->source()->point().x();
//             double y = ((Halfedge_handle)ec)->source()->point().y();
//             Rcpp::Rcout << "x: " << x << " y: " << y << std::endl;
//             coordX.push_back(x);
//             coordY.push_back(y);
//         } while ( ++ec != ec_start );
//
//         PolygonX.push_back(coordX);
//         PolygonY.push_back(coordY);
//
//     }
//
//       return(
//         Rcpp::List::create(
//           Rcpp::Named("x")=PolygonX,
//           Rcpp::Named("y")=PolygonY
//         )
//       );
//
// }
