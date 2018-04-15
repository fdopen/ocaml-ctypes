/*
 * Copyright (c) 2016 Andy Ray.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 */

#ifndef CTYPES_LDOUBLE_STUBS_H
#define CTYPES_LDOUBLE_STUBS_H

#include <caml/mlvalues.h>
#include "ctypes_types.h"

extern value ctypes_copy_ldouble(long double u);
extern long double ctypes_ldouble_val(value);
extern value ctypes_ldouble_of_float(value a);
extern value ctypes_ldouble_to_float(value a);

extern value ctypes_copy_ldouble_complex(ctypes_ldcomplex u);
extern ctypes_ldcomplex ctypes_ldouble_complex_val(value);
extern value ctypes_ldouble_complex_make(value r, value i);
extern value ctypes_ldouble_complex_real(value v);
extern value ctypes_ldouble_complex_imag(value v);

#endif /* CTYPES_LDOUBLE_STUBS_H */
