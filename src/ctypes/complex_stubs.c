/*
 * Copyright (c) 2013 Jeremy Yallop.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 */

#include <caml/memory.h>
#include <caml/alloc.h>

#include "ctypes_complex_stubs.h"
#include "complex_helper.h"

static value allocate_complex_value(double r, double i)
{
  value v = caml_alloc(2 * sizeof(double), Double_array_tag);
  Store_double_field(v, 0, r);
  Store_double_field(v, 1, i);
  return v;
}

/* ctypes_copy_float_complex : float complex -> Complex.t */
value ctypes_copy_float_complex(ctypes_fcomplex c)
{
  return allocate_complex_value(ctypes_crealf(c), ctypes_cimagf(c));
}

/* ctypes_copy_double_complex : double complex -> Complex.t */
value ctypes_copy_double_complex(ctypes_dcomplex c)
{
  return allocate_complex_value(ctypes_creal(c), ctypes_cimag(c));
}

/* ctypes_float_complex_val : Complex.t -> float complex */
ctypes_fcomplex ctypes_float_complex_val(value v)
{
  return (CBUILD_F(Double_field(v, 0), Double_field(v, 1)));
}

/* ctypes_double_complex_val : Complex.t -> double complex */
ctypes_dcomplex ctypes_double_complex_val(value v)
{
  return (CBUILD_D(Double_field(v, 0), Double_field(v, 1)));
}
