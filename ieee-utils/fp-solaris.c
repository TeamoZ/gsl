#include <math.h>
#include <ieeefp.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_errno.h>

int
gsl_ieee_set_mode (int precision, int rounding, int exception_mask)
{
  fp_except mode = 0 ;
  fp_rnd    rnd  = 0 ;

  switch (precision)
    {
    case GSL_IEEE_SINGLE_PRECISION:
      GSL_ERROR ("solaris only supports default precision rounding",
		 GSL_EUNSUP) ;
      break ;
    case GSL_IEEE_DOUBLE_PRECISION:
      GSL_ERROR ("solaris only supports default precision rounding",
		 GSL_EUNSUP) ;
      break ;
    case GSL_IEEE_EXTENDED_PRECISION:
      GSL_ERROR ("solaris only supports default precision rounding",
		 GSL_EUNSUP) ;
      break ;
    }

  switch (rounding)
    {
    case GSL_IEEE_ROUND_TO_NEAREST:
      rnd = FP_RN ;
      fpsetround (rnd) ;
      break ;
    case GSL_IEEE_ROUND_DOWN:
      rnd = FP_RM ;
      fpsetround (rnd) ;
      break ;
    case GSL_IEEE_ROUND_UP:
      rnd = FP_RP ;
      fpsetround (rnd) ;
      break ;
    case GSL_IEEE_ROUND_TO_ZERO:
      rnd = FP_RZ ;
      fpsetround (rnd) ;
      break ;
    default:
      rnd = FP_RN ;
      fpsetround (rnd) ;
    }

  /* Turn on all the exceptions apart from 'inexact' */

  mode = FP_X_INV | FP_X_DZ | FP_X_OFL | FP_X_UFL ;

  if (exception_mask & GSL_IEEE_MASK_INVALID)
    mode &= ~ FP_X_INV ;

  if (exception_mask & GSL_IEEE_MASK_DENORMALIZED)
    GSL_ERROR ("solaris does not support the denormalized operand exception. "
	       "Use 'mask-denormalized' to work around this.",
	       GSL_EUNSUP) ;

  if (exception_mask & GSL_IEEE_MASK_DIVISION_BY_ZERO)
    mode &= ~ FP_X_DZ ;

  if (exception_mask & GSL_IEEE_MASK_OVERFLOW)
    mode &= ~ FP_X_OFL ;

  if (exception_mask & GSL_IEEE_MASK_UNDERFLOW)
    mode &=  ~ FP_X_UFL ;

  if (exception_mask & GSL_IEEE_TRAP_INEXACT)
    {
      mode |= FP_X_IMP ;
    }
  else
    {
      mode &= ~ FP_X_IMP ;
    }

  fpsetmask (mode) ;

  return GSL_SUCCESS ;

}
