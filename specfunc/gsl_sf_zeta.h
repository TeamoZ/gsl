/* Author:  G. Jungman
 * RCS:     $Id$
 */
#ifndef GSL_SF_ZETA_H_
#define GSL_SF_ZETA_H_

#include <gsl/gsl_sf_result.h>


/* Riemann Zeta Function
 * zeta(n) = Sum[ k^(-n), {k,1,Infinity} ]
 *
 * n=integer, n != 1
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
int gsl_sf_zeta_int_impl(int n, gsl_sf_result * result);
int gsl_sf_zeta_int_e(int n, gsl_sf_result * result);


/* Riemann Zeta Function
 * zeta(x) = Sum[ k^(-s), {k,1,Infinity} ], s != 1.0
 *
 * s != 1.0
 * exceptions: GSL_EDOM, GSL_EOVRFLW
 */
int gsl_sf_zeta_impl(double s, gsl_sf_result * result);
int gsl_sf_zeta_e(double s, gsl_sf_result * result);


/* Hurwicz Zeta Function
 * zeta(s,q) = Sum[ (k+q)^(-s), {k,0,Infinity} ]
 *
 * s > 1.0, q > 0.0
 * exceptions: GSL_EDOM, GSL_EUNDRFLW, GSL_EOVRFLW
 */
int gsl_sf_hzeta_impl(double s, double q, gsl_sf_result * result);
int gsl_sf_hzeta_e(double s, double q, gsl_sf_result * result);


/* Eta Function
 * eta(n) = (1-2^(1-n)) zeta(n)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int gsl_sf_eta_int_impl(int n, gsl_sf_result * result);
int gsl_sf_eta_int_e(int n, gsl_sf_result * result);


/* Eta Function
 * eta(s) = (1-2^(1-s)) zeta(s)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int gsl_sf_eta_impl(double s, gsl_sf_result * result);
int gsl_sf_eta_e(double s, gsl_sf_result * result);


#endif  /* !GSL_SF_ZETA_H_ */
