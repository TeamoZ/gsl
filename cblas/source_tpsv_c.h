/* blas/source_tpsv_c.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

{
  const int conj = (TransA == CblasConjTrans) ? -1 : 1;
  const int Trans = (TransA != CblasConjTrans) ? TransA : CblasTrans;
  const int nonunit = (Diag == CblasNonUnit);
  size_t i, j;
  size_t ix, jx;

  if (N == 0)
    return;

  /* form  x := inv( A )*x */

  if ((order == CblasRowMajor && Trans == CblasNoTrans && Uplo == CblasUpper)
      || (order == CblasColMajor && Trans == CblasTrans && Uplo == CblasLower)) {

    ix = OFFSET(N, incX) + incX * (N - 1);

    if (nonunit) {
      const BASE a_real = REAL(Ap, TPUP(N, (N - 1), (N - 1)));
      const BASE a_imag = conj * IMAG(Ap, TPUP(N, (N - 1), (N - 1)));
      const BASE x_real = REAL(X, ix);
      const BASE x_imag = IMAG(X, ix);
      const BASE s = hypot(a_real, a_imag);
      const BASE b_real = a_real / s;
      const BASE b_imag = a_imag / s;
      REAL(X, ix) = (x_real * b_real + x_imag * b_imag) / s;
      IMAG(X, ix) = (x_imag * b_real - b_imag * x_real) / s;
    }

    ix -= incX;

    for (i = N - 1; i > 0 && i--;) {
      BASE tmp_real = REAL(X, ix);
      BASE tmp_imag = IMAG(X, ix);
      jx = ix + incX;
      for (j = i + 1; j < N; j++) {
	const BASE Aij_real = REAL(Ap, TPUP(N, i, j));
	const BASE Aij_imag = conj * IMAG(Ap, TPUP(N, i, j));
	const BASE x_real = REAL(X, jx);
	const BASE x_imag = IMAG(X, jx);
	tmp_real -= Aij_real * x_real - Aij_imag * x_imag;
	tmp_imag -= Aij_real * x_imag + Aij_imag * x_real;
	jx += incX;
      }

      if (nonunit) {
	const BASE a_real = REAL(Ap, TPUP(N, i, i));
	const BASE a_imag = conj * IMAG(Ap, TPUP(N, i, i));
	const BASE s = hypot(a_real, a_imag);
	const BASE b_real = a_real / s;
	const BASE b_imag = a_imag / s;
	REAL(X, ix) = (tmp_real * b_real + tmp_imag * b_imag) / s;
	IMAG(X, ix) = (tmp_imag * b_real - tmp_real * b_imag) / s;
      } else {
	REAL(X, ix) = tmp_real;
	IMAG(X, ix) = tmp_imag;
      }
      ix -= incX;
    }

  } else if ((order == CblasRowMajor && Trans == CblasNoTrans && Uplo == CblasLower)
	     || (order == CblasColMajor && Trans == CblasTrans && Uplo == CblasUpper)) {
    /* forward substitution */

    ix = OFFSET(N, incX);

    if (nonunit) {
      const BASE a_real = REAL(Ap, TPLO(N, 0, 0));
      const BASE a_imag = conj * IMAG(Ap, TPLO(N, 0, 0));
      const BASE x_real = REAL(X, ix);
      const BASE x_imag = IMAG(X, ix);
      const BASE s = hypot(a_real, a_imag);
      const BASE b_real = a_real / s;
      const BASE b_imag = a_imag / s;
      REAL(X, ix) = (x_real * b_real + x_imag * b_imag) / s;
      IMAG(X, ix) = (x_imag * b_real - b_imag * x_real) / s;
    }

    ix += incX;

    for (i = 1; i < N; i++) {
      BASE tmp_real = REAL(X, ix);
      BASE tmp_imag = IMAG(X, ix);
      jx = OFFSET(N, incX);
      for (j = 0; j < i; j++) {
	const BASE Aij_real = REAL(Ap, TPLO(N, i, j));
	const BASE Aij_imag = conj * IMAG(Ap, TPLO(N, i, j));
	const BASE x_real = REAL(X, jx);
	const BASE x_imag = IMAG(X, jx);
	tmp_real -= Aij_real * x_real - Aij_imag * x_imag;
	tmp_imag -= Aij_real * x_imag + Aij_imag * x_real;
	jx += incX;
      }
      if (nonunit) {
	const BASE a_real = REAL(Ap, TPLO(N, i, i));
	const BASE a_imag = conj * IMAG(Ap, TPLO(N, i, i));
	const BASE s = hypot(a_real, a_imag);
	const BASE b_real = a_real / s;
	const BASE b_imag = a_imag / s;
	REAL(X, ix) = (tmp_real * b_real + tmp_imag * b_imag) / s;
	IMAG(X, ix) = (tmp_imag * b_real - tmp_real * b_imag) / s;
      } else {
	REAL(X, ix) = tmp_real;
	IMAG(X, ix) = tmp_imag;
      }
      ix += incX;
    }
  } else if ((order == CblasRowMajor && Trans == CblasTrans && Uplo == CblasUpper)
	     || (order == CblasColMajor && Trans == CblasNoTrans && Uplo == CblasLower)) {
    /* form  x := inv( A' )*x */

    /* forward substitution */

    ix = OFFSET(N, incX);

    if (nonunit) {
      const BASE a_real = REAL(Ap, TPUP(N, 0, 0));
      const BASE a_imag = conj * IMAG(Ap, TPUP(N, 0, 0));
      const BASE x_real = REAL(X, ix);
      const BASE x_imag = IMAG(X, ix);
      const BASE s = hypot(a_real, a_imag);
      const BASE b_real = a_real / s;
      const BASE b_imag = a_imag / s;
      REAL(X, ix) = (x_real * b_real + x_imag * b_imag) / s;
      IMAG(X, ix) = (x_imag * b_real - b_imag * x_real) / s;
    }

    ix += incX;

    for (i = 1; i < N; i++) {
      BASE tmp_real = REAL(X, ix);
      BASE tmp_imag = IMAG(X, ix);
      jx = OFFSET(N, incX);
      for (j = 0; j < i; j++) {
	const BASE Aij_real = REAL(Ap, TPUP(N, j, i));
	const BASE Aij_imag = conj * IMAG(Ap, TPUP(N, j, i));
	const BASE x_real = REAL(X, jx);
	const BASE x_imag = IMAG(X, jx);
	tmp_real -= Aij_real * x_real - Aij_imag * x_imag;
	tmp_imag -= Aij_real * x_imag + Aij_imag * x_real;
	jx += incX;
      }
      if (nonunit) {
	const BASE a_real = REAL(Ap, TPUP(N, i, i));
	const BASE a_imag = conj * IMAG(Ap, TPUP(N, i, i));
	const BASE s = hypot(a_real, a_imag);
	const BASE b_real = a_real / s;
	const BASE b_imag = a_imag / s;
	REAL(X, ix) = (tmp_real * b_real + tmp_imag * b_imag) / s;
	IMAG(X, ix) = (tmp_imag * b_real - tmp_real * b_imag) / s;
      } else {
	REAL(X, ix) = tmp_real;
	IMAG(X, ix) = tmp_imag;
      }
      ix += incX;
    }
  } else if ((order == CblasRowMajor && Trans == CblasTrans && Uplo == CblasLower)
	     || (order == CblasColMajor && Trans == CblasNoTrans && Uplo == CblasUpper)) {

    /* backsubstitution */

    ix = OFFSET(N, incX) + incX * (N - 1);

    if (nonunit) {
      const BASE a_real = REAL(Ap, TPLO(N, (N - 1), (N - 1)));
      const BASE a_imag = conj * IMAG(Ap, TPLO(N, (N - 1), (N - 1)));
      const BASE x_real = REAL(X, ix);
      const BASE x_imag = IMAG(X, ix);
      const BASE s = hypot(a_real, a_imag);
      const BASE b_real = a_real / s;
      const BASE b_imag = a_imag / s;
      REAL(X, ix) = (x_real * b_real + x_imag * b_imag) / s;
      IMAG(X, ix) = (x_imag * b_real - b_imag * x_real) / s;
    }

    ix -= incX;

    for (i = N - 1; i > 0 && i--;) {
      BASE tmp_real = REAL(X, ix);
      BASE tmp_imag = IMAG(X, ix);
      jx = ix + incX;
      for (j = i + 1; j < N; j++) {
	const BASE Aij_real = REAL(Ap, TPLO(N, j, i));
	const BASE Aij_imag = conj * IMAG(Ap, TPLO(N, j, i));
	const BASE x_real = REAL(X, jx);
	const BASE x_imag = IMAG(X, jx);
	tmp_real -= Aij_real * x_real - Aij_imag * x_imag;
	tmp_imag -= Aij_real * x_imag + Aij_imag * x_real;
	jx += incX;
      }

      if (nonunit) {
	const BASE a_real = REAL(Ap, TPLO(N, i, i));
	const BASE a_imag = conj * IMAG(Ap, TPLO(N, i, i));
	const BASE s = hypot(a_real, a_imag);
	const BASE b_real = a_real / s;
	const BASE b_imag = a_imag / s;
	REAL(X, ix) = (tmp_real * b_real + tmp_imag * b_imag) / s;
	IMAG(X, ix) = (tmp_imag * b_real - tmp_real * b_imag) / s;
      } else {
	REAL(X, ix) = tmp_real;
	IMAG(X, ix) = tmp_imag;
      }
      ix -= incX;
    }
  } else {
    BLAS_ERROR("unrecognized operation");
  }
}