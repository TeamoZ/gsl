#ifndef GSL_VECTOR_H 
#define GSL_VECTOR_H 

#include <stdlib.h>
#include <gsl_errno.h>

typedef struct
{
  size_t size;
  double * data;
} gsl_vector ;

gsl_vector * gsl_vector_alloc (size_t n);
gsl_vector * gsl_vector_calloc (size_t n);
void gsl_vector_free (gsl_vector * v);

double gsl_vector_get(const gsl_vector * v, const size_t i);
void gsl_vector_set(gsl_vector * v, const size_t i, const double x);

int gsl_vector_fread (FILE * stream, gsl_vector * v) ;
int gsl_vector_fwrite (FILE * stream, const gsl_vector * v) ;
int gsl_vector_fscanf (FILE * stream, gsl_vector * v);
int gsl_vector_fprintf (FILE * stream, const gsl_vector * v, const char * format);

int gsl_block_fread (FILE * stream, double * data, size_t n) ;
int gsl_block_fwrite (FILE * stream, const double * data, size_t n) ;
int gsl_block_fscanf (FILE * stream, double * data, size_t n);
int gsl_block_fprintf (FILE * stream, const double * data, size_t n,
		       const char * format);

extern int gsl_check_range ;

/* inline functions if you are using GCC */

#ifndef __STRICT_ANSI__
extern inline 
double
gsl_vector_get(const gsl_vector * v, const size_t i)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= v->size) /* size_t is unsigned, can't be negative */
    {
      GSL_ERROR_RETURN("index out of range", GSL_EINVAL, 0) ;
    }
#endif
  return v->data[i] ;
} 

extern inline 
void
gsl_vector_set(gsl_vector * v, const size_t i, const double x)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= v->size) /* size_t is unsigned, can't be negative */
    {
      GSL_ERROR_RETURN_NOTHING("index out of range", GSL_EINVAL) ;
    }
#endif
  v->data[i] = x ;
}
#endif

#endif /* GSL_VECTOR_H */
