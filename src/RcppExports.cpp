// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// BoundedUnweightedVoronoi
Rcpp::List BoundedUnweightedVoronoi(const Rcpp::NumericVector& coordX, const Rcpp::NumericVector& coordY, const double& minX, const double& minY, const double& maxX, const double& maxY);
RcppExport SEXP _ComputationalGeometry_BoundedUnweightedVoronoi(SEXP coordXSEXP, SEXP coordYSEXP, SEXP minXSEXP, SEXP minYSEXP, SEXP maxXSEXP, SEXP maxYSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordX(coordXSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordY(coordYSEXP);
    Rcpp::traits::input_parameter< const double& >::type minX(minXSEXP);
    Rcpp::traits::input_parameter< const double& >::type minY(minYSEXP);
    Rcpp::traits::input_parameter< const double& >::type maxX(maxXSEXP);
    Rcpp::traits::input_parameter< const double& >::type maxY(maxYSEXP);
    rcpp_result_gen = Rcpp::wrap(BoundedUnweightedVoronoi(coordX, coordY, minX, minY, maxX, maxY));
    return rcpp_result_gen;
END_RCPP
}
// BoundedWeightedVoronoi
Rcpp::List BoundedWeightedVoronoi(const Rcpp::NumericVector& coordX, const Rcpp::NumericVector& coordY, const Rcpp::NumericVector& Weights, const double& minX, const double& minY, const double& maxX, const double& maxY);
RcppExport SEXP _ComputationalGeometry_BoundedWeightedVoronoi(SEXP coordXSEXP, SEXP coordYSEXP, SEXP WeightsSEXP, SEXP minXSEXP, SEXP minYSEXP, SEXP maxXSEXP, SEXP maxYSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordX(coordXSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordY(coordYSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type Weights(WeightsSEXP);
    Rcpp::traits::input_parameter< const double& >::type minX(minXSEXP);
    Rcpp::traits::input_parameter< const double& >::type minY(minYSEXP);
    Rcpp::traits::input_parameter< const double& >::type maxX(maxXSEXP);
    Rcpp::traits::input_parameter< const double& >::type maxY(maxYSEXP);
    rcpp_result_gen = Rcpp::wrap(BoundedWeightedVoronoi(coordX, coordY, Weights, minX, minY, maxX, maxY));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_hello
List rcpp_hello();
RcppExport SEXP _ComputationalGeometry_rcpp_hello() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(rcpp_hello());
    return rcpp_result_gen;
END_RCPP
}
// test1
void test1();
RcppExport SEXP _ComputationalGeometry_test1() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test1();
    return R_NilValue;
END_RCPP
}
// test2
void test2();
RcppExport SEXP _ComputationalGeometry_test2() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test2();
    return R_NilValue;
END_RCPP
}
// test3
void test3();
RcppExport SEXP _ComputationalGeometry_test3() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test3();
    return R_NilValue;
END_RCPP
}
// test4
void test4();
RcppExport SEXP _ComputationalGeometry_test4() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test4();
    return R_NilValue;
END_RCPP
}
// test5
void test5();
RcppExport SEXP _ComputationalGeometry_test5() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test5();
    return R_NilValue;
END_RCPP
}
// test6bis
void test6bis();
RcppExport SEXP _ComputationalGeometry_test6bis() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test6bis();
    return R_NilValue;
END_RCPP
}
// voronoiTreemap
Rcpp::List voronoiTreemap(const Rcpp::NumericVector& coordX, const Rcpp::NumericVector& coordY, const Rcpp::NumericVector& Weights, const double& minX, const double& minY, const double& maxX, const double& maxY);
RcppExport SEXP _ComputationalGeometry_voronoiTreemap(SEXP coordXSEXP, SEXP coordYSEXP, SEXP WeightsSEXP, SEXP minXSEXP, SEXP minYSEXP, SEXP maxXSEXP, SEXP maxYSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordX(coordXSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordY(coordYSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type Weights(WeightsSEXP);
    Rcpp::traits::input_parameter< const double& >::type minX(minXSEXP);
    Rcpp::traits::input_parameter< const double& >::type minY(minYSEXP);
    Rcpp::traits::input_parameter< const double& >::type maxX(maxXSEXP);
    Rcpp::traits::input_parameter< const double& >::type maxY(maxYSEXP);
    rcpp_result_gen = Rcpp::wrap(voronoiTreemap(coordX, coordY, Weights, minX, minY, maxX, maxY));
    return rcpp_result_gen;
END_RCPP
}
// UnboundedUnweightedVoronoi
Rcpp::List UnboundedUnweightedVoronoi(const Rcpp::NumericVector& coordX, const Rcpp::NumericVector& coordY);
RcppExport SEXP _ComputationalGeometry_UnboundedUnweightedVoronoi(SEXP coordXSEXP, SEXP coordYSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordX(coordXSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordY(coordYSEXP);
    rcpp_result_gen = Rcpp::wrap(UnboundedUnweightedVoronoi(coordX, coordY));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ComputationalGeometry_BoundedUnweightedVoronoi", (DL_FUNC) &_ComputationalGeometry_BoundedUnweightedVoronoi, 6},
    {"_ComputationalGeometry_BoundedWeightedVoronoi", (DL_FUNC) &_ComputationalGeometry_BoundedWeightedVoronoi, 7},
    {"_ComputationalGeometry_rcpp_hello", (DL_FUNC) &_ComputationalGeometry_rcpp_hello, 0},
    {"_ComputationalGeometry_test1", (DL_FUNC) &_ComputationalGeometry_test1, 0},
    {"_ComputationalGeometry_test2", (DL_FUNC) &_ComputationalGeometry_test2, 0},
    {"_ComputationalGeometry_test3", (DL_FUNC) &_ComputationalGeometry_test3, 0},
    {"_ComputationalGeometry_test4", (DL_FUNC) &_ComputationalGeometry_test4, 0},
    {"_ComputationalGeometry_test5", (DL_FUNC) &_ComputationalGeometry_test5, 0},
    {"_ComputationalGeometry_test6bis", (DL_FUNC) &_ComputationalGeometry_test6bis, 0},
    {"_ComputationalGeometry_voronoiTreemap", (DL_FUNC) &_ComputationalGeometry_voronoiTreemap, 7},
    {"_ComputationalGeometry_UnboundedUnweightedVoronoi", (DL_FUNC) &_ComputationalGeometry_UnboundedUnweightedVoronoi, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_ComputationalGeometry(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
