#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_test.h>

#define CHECK(x) errors[n].number = x ; errors[n].name = #x ; n++ ;
#define MAX_ERRS 32

int verbose = 0 ;

int
main (void)
{
  int i, j, n = 0 ;

  struct { 
    int number; 
    const char * name; 
  } errors[MAX_ERRS] ;

  CHECK(GSL_SUCCESS);
  CHECK(GSL_FAILURE);
  CHECK(GSL_CONTINUE);
  CHECK(GSL_EDOM);
  CHECK(GSL_ERANGE);
  CHECK(GSL_EFAULT);
  CHECK(GSL_EINVAL);
  CHECK(GSL_EFAILED);
  CHECK(GSL_EFACTOR);
  CHECK(GSL_ESANITY);
  CHECK(GSL_ENOMEM);
  CHECK(GSL_EBADFUNC);
  CHECK(GSL_ERUNAWAY);
  CHECK(GSL_EMAXITER);
  CHECK(GSL_EZERODIV);
  CHECK(GSL_EBADTOL);
  CHECK(GSL_ETOL);
  CHECK(GSL_EUNDRFLW);
  CHECK(GSL_EOVRFLW);
  CHECK(GSL_ELOSS);
  CHECK(GSL_EROUND);
  CHECK(GSL_EBADLEN);
  CHECK(GSL_ENOTSQR);
  CHECK(GSL_ESING);
  CHECK(GSL_EDIVERGE);
  CHECK(GSL_EUNSUP);
  CHECK(GSL_EUNIMPL);
  CHECK(GSL_ECACHE);
  CHECK(GSL_ENOPROG);
  CHECK(GSL_ENOPROGJ);

  for (i = 0 ; i < n ; i++) 
    {
      if (verbose) printf ("%s = %d\n", errors[i].name, errors[i].number) ;
    }

  for (i = 0; i < n; i++)
    {
      int status = 0;
      for (j = 0; j < n; j++)
	{
	  if (j != i)
	      status |= (errors[i].number == errors[j].number);
	}

      gsl_test (status, "%s is distinct from other error values",
		errors[i].name);
    }

  for (i = 0; i < n; i++)
    {
      int status = 0;
      int e1 = errors[i].number ;
      for (j = 0; j < n; j++)
	{
	  if (j != i)
	    {
	      int e2 = errors[j].number;
	      status |= (gsl_strerror(e1) == gsl_strerror(e2)) ;
	    }
	}
      gsl_test (status, "%s has a distinct error message",
		errors[i].name);
    }

  
  return gsl_test_summary ();
}

