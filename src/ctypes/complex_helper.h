/*
 * Copyright (c) 2018 Andreas Hauptmann
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 */

#ifndef CTYPES_COMPLEX_HELPER_H
#define CTYPES_COMPLEX_HELPER_H

#include "ctypes_types.h"

#if CTYPES_COMPLEX_STRUCTURE
#include <math.h>

#define CTYPES_COMPLEX_BUILDER(tstruct, tb, name)                       \
  static inline tstruct ctypes_complex_add_ ## name(tstruct l, tstruct r) \
  {                                                                     \
    tstruct res;                                                        \
    res._Val[0] = l._Val[0] + r._Val[0];                                \
    res._Val[1] = l._Val[1] + r._Val[1];                                \
    return res;                                                         \
  }                                                                     \
  static inline tstruct ctypes_complex_sub_ ## name(tstruct l, tstruct r) \
  {                                                                     \
    tstruct res;                                                        \
    res._Val[0] = l._Val[0] - r._Val[0];                                \
    res._Val[1] = l._Val[1] - r._Val[1];                                \
    return res;                                                         \
  }                                                                     \
  static inline tstruct ctypes_complex_mul_ ## name(tstruct l, tstruct r) \
  {                                                                     \
    tstruct res;                                                        \
    tb ac, bd, ad, bc, x, y;                                            \
    tb a = l._Val[0];                                                   \
    tb b = l._Val[1];                                                   \
    tb c = r._Val[0];                                                   \
    tb d = r._Val[1];                                                   \
    /* See C99 Standard Appendix G.5.1 , EXAMPLE 1 */                   \
    ac = a * c;                                                         \
    bd = b * d;                                                         \
    ad = a * d;                                                         \
    bc = b * c;                                                         \
    x = ac - bd;                                                        \
    y = ad + bc;                                                        \
    if ( isnan(x) && isnan(y) ) {                                       \
      int recalc = 0;                                                   \
      if ( isinf(a) || isinf(b) ) {                                     \
        a = copysign( isinf(a) ? 1.0 : 0.0, a );                        \
        b = copysign( isinf(b) ? 1.0 : 0.0, b );                        \
        if ( isnan(c) ) {                                               \
          c = copysign(0.0, c);                                         \
        }                                                               \
        if ( isnan(d) ) {                                               \
          d = copysign(0.0, d);                                         \
        }                                                               \
        recalc = 1;                                                     \
      }                                                                 \
      if ( isinf(c) || isinf(d) )	{                                     \
        c = copysign( isinf(c) ? 1.0 : 0.0, c );                        \
        d = copysign( isinf(d) ? 1.0 : 0.0, d );                        \
        if ( isnan(a) ) {                                               \
          a = copysign(0.0, a);                                         \
        }                                                               \
        if ( isnan(b) ) {                                               \
          b = copysign(0.0, b);                                         \
        }                                                               \
        recalc = 1;                                                     \
      }                                                                 \
      if ( !recalc && ( isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc) ) ) { \
        if ( isnan(a) ) {                                               \
          a = copysign(0.0, a);                                         \
        }                                                               \
        if ( isnan(b) ) {                                               \
          b = copysign(0.0, b);                                         \
        }                                                               \
        if ( isnan(c) ) {                                               \
          c = copysign(0.0, c);                                         \
        }                                                               \
        if ( isnan(d) ) {                                               \
          d = copysign(0.0, d);                                         \
        }                                                               \
        recalc = 1;                                                     \
      }                                                                 \
      if (recalc) {                                                     \
        x = INFINITY * (a * c - b * d);                                 \
        y = INFINITY * (a * d + b * c);                                 \
      }                                                                 \
    }                                                                   \
    res._Val[0] = x;                                                    \
    res._Val[1] = y;                                                    \
    return res;                                                         \
  }                                                                     \
  static inline tstruct ctypes_complex_div_ ## name(tstruct l, tstruct r) \
  {                                                                     \
    tstruct res;                                                        \
    tb denom, ratio, x, y;                                              \
    tb a = l._Val[0];                                                   \
    tb b = l._Val[1];                                                   \
    tb c = r._Val[0];                                                   \
    tb d = r._Val[1];                                                   \
    /* scalbn would be better, but it's C99, where this code isn't used  */ \
    if ( fabs(c) >= fabs(d) ) {                                         \
      ratio = d / c;                                                    \
      denom = c + d * ratio;                                            \
      x = (a + b * ratio) / denom;                                      \
      y = (b - a * ratio) / denom;                                      \
    }                                                                   \
    else {                                                              \
      ratio = c / d;                                                    \
      denom = d + c * ratio;                                            \
      x = (a * ratio + b) / denom;                                      \
      y = (b * ratio - a) / denom;                                      \
    }                                                                   \
    /* See C99 Standard Appendix G.5.1 , EXAMPLE 2 */                   \
    if ( isnan(x) && isnan(y) ) {                                       \
      if ( c == 0.0 && d == 0.0 && ( !isnan(a) || !isnan (b) ) ) {      \
        x = copysign(INFINITY, c) * a;                                  \
        y = copysign(INFINITY, c) * b;                                  \
      }                                                                 \
      else if ( (isinf(a) || isinf(b) ) && isfinite(c) && isfinite(d) ) { \
        a = copysign( isinf(a) ? 1.0 : 0.0 , a );                       \
        b = copysign( isinf(b) ? 1.0 : 0.0 , b );                       \
        x = INFINITY * (a * c + b * d);                                 \
        y = INFINITY * (b * c - a * d);                                 \
      }                                                                 \
      else if ( (isinf(c) || isinf(d) ) && isfinite(a) && isfinite(b) ) { \
        c = copysign( isinf(c) ? 1.0 : 0.0 , c );                       \
        d = copysign( isinf(d) ? 1 : 0.0 , d );                         \
        x = 0.0 * (a * c + b * d);                                      \
        y = 0.0 * (b * c - a * d);                                      \
      }                                                                 \
    }                                                                   \
    res._Val[0] = x;                                                    \
    res._Val[1] = y;                                                    \
    return res;                                                         \
  }                                                                     \
  static inline tstruct ctypes_complex_neg_ ## name(tstruct l)          \
  {                                                                     \
    tstruct res;                                                        \
    res._Val[0] = -l._Val[0];                                           \
    res._Val[1] = -l._Val[1];                                           \
    return res;                                                         \
  }                                                                     \
  static inline tstruct ctypes_complex_build_ ## name(tb re, tb im)     \
  {                                                                     \
    tstruct res;                                                        \
    res._Val[0] = re;                                                   \
    res._Val[1] = im;                                                   \
    return res;                                                         \
  }

CTYPES_COMPLEX_BUILDER(ctypes_fcomplex, float, float)
CTYPES_COMPLEX_BUILDER(ctypes_dcomplex, double, double)
CTYPES_COMPLEX_BUILDER(ctypes_ldcomplex, long double, long_double)
#undef CTYPES_COMPLEX_BUILDER

#define CADD_F ctypes_complex_add_float
#define CADD_D ctypes_complex_add_double
#define CADD_LD ctypes_complex_add_long_double

#define CSUB_F ctypes_complex_sub_float
#define CSUB_D ctypes_complex_sub_double
#define CSUB_LD ctypes_complex_sub_long_double

#define CMUL_F ctypes_complex_mul_float
#define CMUL_D ctypes_complex_mul_double
#define CMUL_LD ctypes_complex_mul_long_double

#define CDIV_F ctypes_complex_div_float
#define CDIV_D ctypes_complex_div_double
#define CDIV_LD ctypes_complex_div_long_double

#define CNEG_F ctypes_complex_neg_float
#define CNEG_D ctypes_complex_neg_double
#define CNEG_LD ctypes_complex_neg_long_double

#define CBUILD_F ctypes_complex_build_float
#define CBUILD_D ctypes_complex_build_double
#define CBUILD_LD ctypes_complex_build_long_double

#define ctypes_creal(x) ((double)((x)._Val[0]))
#define ctypes_crealf(x) ((float)((x)._Val[0]))
#define ctypes_creall(x) ((long double)((x)._Val[0]))

#define ctypes_cimag(x) ((double)((x)._Val[1]))
#define ctypes_cimagf(x) ((float)((x)._Val[1]))
#define ctypes_cimagl(x) ((long double)((x)._Val[1]))

#else /* #if CTYPES_COMPLEX_STRUCTURE */

#define CADD_F(a,b) ((a) + (b))
#define CADD_D CADD_F
#define CADD_LD CADD_F

#define CSUB_F(a,b) ((a) - (b))
#define CSUB_D CSUB_F
#define CSUB_LD CSUB_F

#define CMUL_F(a,b) ((a) * (b))
#define CMUL_D CMUL_F
#define CMUL_LD CMUL_F

#define CDIV_F(a,b) ((a) / (b))
#define CDIV_D CDIV_F
#define CDIV_LD CDIV_F

#define CNEG_F(a) (-(a))
#define CNEG_D CNEG_F
#define CNEG_LD CNEG_F

/* It's not possible to use the C99 literal syntax
   (`double complex c = re + im * I`) to initialize complex numbers,
   e.g. `0.0 + ((1./0.) * I)` might give NaN as the real part. */

#if defined(CTYPES_HAVE_COMPLEX_H) && defined(CMPLXF) && defined(CMPLX) && defined(CMPLXL)
/* macros introduced by C11 to circumvent the problem mentioned above */
#define CBUILD_F CMPLXF
#define CBUILD_D CMPLX
#define CBUILD_LD CMPLXL
#elif defined(__clang__)
#  define CBUILD_F(re,im) ((float complex){re,im})
#  define CBUILD_D(re,im) ((double complex){re,im})
#  define CBUILD_LD(re,im) ((long double complex){re,im})
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
#  define CBUILD_F(re,im) __builtin_complex((float)(re), (float)(im))
#  define CBUILD_D(re,im) __builtin_complex((double)(re), (double)(im))
#  define CBUILD_LD(re,im) __builtin_complex((long double)(re), (long double)(im))
#else

/* C99:
   Each complex type has the same representation and alignment
   requirements as an array type containing exactly two elements of the
   corresponding real type; the first element is equal to the real part,
   and the second element to the imaginary part, of the complex number. */

#define CTYPES_COMPLEX_BUILDER(FNAME, ctypes_type, ctype) \
  static inline ctypes_type FNAME(ctype re, ctype im)     \
  {                                                       \
    union {                                               \
      ctype ar[2];                                        \
      ctypes_type c;                                      \
    } h;                                                  \
    h.ar[0] = re;                                         \
    h.ar[1] = im;                                         \
    return (h.c);                                         \
  }

CTYPES_COMPLEX_BUILDER(CBUILD_F,ctypes_fcomplex,float)
CTYPES_COMPLEX_BUILDER(CBUILD_D,ctypes_dcomplex,double)
CTYPES_COMPLEX_BUILDER(CBUILD_LD,ctypes_ldcomplex,long double)
#undef CTYPES_COMPLEX_BUILDER

#endif

#if CTYPES_HAVE_COMPLEX_H

#define ctypes_creal creal
#define ctypes_crealf crealf
#define ctypes_creall creall
#define ctypes_cimag cimag
#define ctypes_cimagf cimagf
#define ctypes_cimagl cimagl

#elif (defined(__GNUC__) && __GNUC__ >= 4) ||         \
  (defined(__clang_major__) && __clang_major__ >= 3)

#define ctypes_creal __builtin_creal
#define ctypes_crealf __builtin_crealf
#define ctypes_creall __builtin_creall
#define ctypes_cimag __builtin_cimag
#define ctypes_cimagf __builtin_cimagf
#define ctypes_cimagl __builtin_cimagl

#else

#define CTYPES_COMPLEX_ACCESS(FNAME, ctypes_type, ctype,n)  \
  static inline ctype FNAME(ctypes_type v)                  \
  {                                                         \
    union {                                                 \
      ctype ar[2];                                          \
      ctypes_type c;                                        \
    } h;                                                    \
    h.c = v;                                                \
    return (h.ar[n]);                                       \
  }

CTYPES_COMPLEX_ACCESS(ctypes_creal, ctypes_dcomplex, double, 0)
CTYPES_COMPLEX_ACCESS(ctypes_crealf, ctypes_fcomplex, float, 0)
CTYPES_COMPLEX_ACCESS(ctypes_creall, ctypes_ldcomplex, long double, 0)
CTYPES_COMPLEX_ACCESS(ctypes_cimag, ctypes_dcomplex, double, 1)
CTYPES_COMPLEX_ACCESS(ctypes_cimagf, ctypes_fcomplex, float, 1)
CTYPES_COMPLEX_ACCESS(ctypes_cimagl, ctypes_ldcomplex, long double, 1)
#undef CTYPES_COMPLEX_ACCESS

#endif /* CTYPES_HAVE_COMPLEX_H */

#endif /* CTYPES_COMPLEX_STRUCTURE */

#endif /* CTYPES_COMPLEX_HELPER_H */
