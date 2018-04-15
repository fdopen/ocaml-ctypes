/*
 * Copyright (c) 2013 Jeremy Yallop.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 */

#ifdef CTYPES_POSIX_TYPES_ENABLED
#undef CTYPES_POSIX_TYPES_ENABLED
#endif
#define CTYPES_POSIX_TYPES_ENABLED 1

#include <caml/mlvalues.h>

#include "ctypes_primitives.h"
#include "ctypes_types.h"

#define EXPOSE_TYPEINFO(TYPENAME)                           \
  value ctypes_typeof_ ## TYPENAME(value unit)              \
  {                                                         \
    enum ctypes_arithmetic_type underlying =                \
      CTYPES_CLASSIFY_ARITHMETIC_TYPE(ctypes_ ## TYPENAME); \
    return Val_int(underlying);                             \
  }

#define EXPOSE_ALIGNMENT(TYPENAME)                  \
  value ctypes_alignmentof_ ## TYPENAME(value unit) \
  {                                                 \
    struct s { char c; ctypes_ ## TYPENAME t; };    \
    return Val_int(offsetof(struct s, t));          \
  }

#define EXPOSE_TYPESIZE(TYPENAME)                 \
  value ctypes_sizeof_ ## TYPENAME(value unit)    \
  {                                               \
    return Val_int(sizeof(ctypes_ ## TYPENAME));  \
  }

EXPOSE_TYPEINFO(clock_t)
EXPOSE_TYPEINFO(dev_t)
EXPOSE_TYPEINFO(ino_t)
EXPOSE_TYPEINFO(off_t)
EXPOSE_TYPEINFO(time_t)
EXPOSE_TYPEINFO(mode_t)
EXPOSE_TYPEINFO(pid_t)
EXPOSE_TYPEINFO(ssize_t)
EXPOSE_TYPEINFO(useconds_t)
EXPOSE_TYPEINFO(nlink_t)
EXPOSE_TYPESIZE(sigset_t)
EXPOSE_ALIGNMENT(sigset_t)
