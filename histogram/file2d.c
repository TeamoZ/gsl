#include <config.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_block.h>
#include <gsl/gsl_histogram2d.h>

int
gsl_histogram2d_fread (FILE * stream, gsl_histogram2d * h)
{
  int status = gsl_block_raw_fread (stream, h->xrange, h->nx + 1, 1);

  if (status)
    return status;

  status = gsl_block_raw_fread (stream, h->yrange, h->ny + 1, 1);

  if (status)
    return status;

  status = gsl_block_raw_fread (stream, h->bin, h->nx * h->ny, 1);

  return status;
}

int
gsl_histogram2d_fwrite (FILE * stream, const gsl_histogram2d * h)
{
  int status = gsl_block_raw_fwrite (stream, h->xrange, h->nx + 1, 1);

  if (status)
    return status;

  status = gsl_block_raw_fwrite (stream, h->yrange, h->ny + 1, 1);

  if (status)
    return status;

  status = gsl_block_raw_fwrite (stream, h->bin, h->nx * h->ny, 1);
  return status;
}

int
gsl_histogram2d_fprintf (FILE * stream, const gsl_histogram2d * h,
			 const char *range_format, const char *bin_format)
{
  size_t i, j;
  const size_t nx = h->nx;
  const size_t ny = h->ny;
  int status;

  for (i = 0; i < nx; i++)
    {
      for (j = 0; j < ny; j++)
	{
	  status = fprintf (stream, range_format, h->xrange[i]);

	  if (status < 0)
	    {
	      GSL_ERROR ("fprintf failed", GSL_EFAILED);
	    }

	  status = putc (' ', stream);

	  if (status == EOF)
	    {
	      GSL_ERROR ("putc failed", GSL_EFAILED);
	    }

	  status = fprintf (stream, range_format, h->xrange[i + 1]);

	  if (status < 0)
	    {
	      GSL_ERROR ("fprintf failed", GSL_EFAILED);
	    }

	  status = putc (' ', stream);

	  if (status == EOF)
	    {
	      GSL_ERROR ("putc failed", GSL_EFAILED);
	    }

	  status = fprintf (stream, range_format, h->yrange[j]);

	  if (status < 0)
	    {
	      GSL_ERROR ("fprintf failed", GSL_EFAILED);
	    }

	  status = putc (' ', stream);

	  if (status == EOF)
	    {
	      GSL_ERROR ("putc failed", GSL_EFAILED);
	    }

	  status = fprintf (stream, range_format, h->yrange[j + 1]);

	  if (status < 0)
	    {
	      GSL_ERROR ("fprintf failed", GSL_EFAILED);
	    }

	  status = putc (' ', stream);

	  if (status == EOF)
	    {
	      GSL_ERROR ("putc failed", GSL_EFAILED);
	    }

	  status = fprintf (stream, bin_format, h->bin[i * ny + j]);

	  if (status < 0)
	    {
	      GSL_ERROR ("fprintf failed", GSL_EFAILED);
	    }

	  status = putc ('\n', stream);

	  if (status == EOF)
	    {
	      GSL_ERROR ("putc failed", GSL_EFAILED);
	    }
	}
      status = putc ('\n', stream);

      if (status == EOF)
	{
	  GSL_ERROR ("putc failed", GSL_EFAILED);
	}
    }

  return 0;
}

int
gsl_histogram2d_fscanf (FILE * stream, gsl_histogram2d * h)
{
  size_t i, j;
  const size_t nx = h->nx;
  const size_t ny = h->ny;
  double xupper, yupper;

  for (i = 0; i < nx; i++)
    {
      for (j = 0; j < ny; j++)
	{
	  int status = fscanf (stream,
			       "%lg %lg %lg %lg %lg",
			       h->xrange + i, &xupper,
			       h->yrange + j, &yupper,
			       h->bin + i * ny + j);

	  if (status != 5)
	    {
	      GSL_ERROR ("fscanf failed", GSL_EFAILED);
	    }
	}
      h->yrange[ny] = yupper;
    }

  h->xrange[nx] = xupper;

  return 0;
}
