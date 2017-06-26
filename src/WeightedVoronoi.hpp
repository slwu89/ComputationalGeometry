////////////////////////////////////////////////////
//
// Sean Wu
// Weighted Voronoi Diagram header file
// June 25, 2017
//
////////////////////////////////////////////////////

#ifndef WEIGHTEDVORONOI_HPP
#define WEIGHTEDVORONOI_HPP

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
typedef ApolloniusGraph_VoronoiDiagram::Halfedge_handle           Halfedge_handle;
typedef ApolloniusGraph_VoronoiDiagram::Ccb_halfedge_circulator   Ccb_halfedge_circulator;

typedef std::vector<double>             vectorDouble;
typedef std::vector<vectorDouble>       vectorPolygon;

#endif
