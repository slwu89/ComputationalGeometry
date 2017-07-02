// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// BoundedUnweightedVoronoi
Rcpp::List BoundedUnweightedVoronoi(const Rcpp::NumericVector& coordX, const Rcpp::NumericVector& coordY, const double& minX, const double& minY, const double& maxX, const double& maxY);
RcppExport SEXP ComputationalGeometry_BoundedUnweightedVoronoi(SEXP coordXSEXP, SEXP coordYSEXP, SEXP minXSEXP, SEXP minYSEXP, SEXP maxXSEXP, SEXP maxYSEXP) {
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
// rcpp_hello
List rcpp_hello();
RcppExport SEXP ComputationalGeometry_rcpp_hello() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(rcpp_hello());
    return rcpp_result_gen;
END_RCPP
}
// WeightedVoronoi
Rcpp::List WeightedVoronoi(const Rcpp::NumericVector& coordX, const Rcpp::NumericVector& coordY, const Rcpp::NumericVector& Weights);
RcppExport SEXP ComputationalGeometry_WeightedVoronoi(SEXP coordXSEXP, SEXP coordYSEXP, SEXP WeightsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordX(coordXSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type coordY(coordYSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type Weights(WeightsSEXP);
    rcpp_result_gen = Rcpp::wrap(WeightedVoronoi(coordX, coordY, Weights));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"ComputationalGeometry_BoundedUnweightedVoronoi", (DL_FUNC) &ComputationalGeometry_BoundedUnweightedVoronoi, 6},
    {"ComputationalGeometry_rcpp_hello", (DL_FUNC) &ComputationalGeometry_rcpp_hello, 0},
    {"ComputationalGeometry_WeightedVoronoi", (DL_FUNC) &ComputationalGeometry_WeightedVoronoi, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_ComputationalGeometry(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
