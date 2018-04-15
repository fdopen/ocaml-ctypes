/*
 * Copyright (c) 2013 Jeremy Yallop.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 */

#ifndef CTYPES_COMPLEX_STUBS_H
#define CTYPES_COMPLEX_STUBS_H

#include <caml/mlvalues.h>
#include "ctypes_types.h"

/* ctypes_copy_float_complex : float complex -> Complex.t */
value ctypes_copy_float_complex(ctypes_fcomplex);

/* ctypes_copy_double_complex : double complex -> Complex.t */
value ctypes_copy_double_complex(ctypes_dcomplex);

/* ctypes_float_complex_val : Complex.t -> float complex */
ctypes_fcomplex ctypes_float_complex_val(value);

/* ctypes_double_complex_val : Complex.t -> double complex */
ctypes_dcomplex ctypes_double_complex_val(value);

#endif /* CTYPES_COMPLEX_STUBS_H */
