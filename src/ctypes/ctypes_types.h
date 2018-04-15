/*
 * Copyright (c) 2018 fdopen.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 */

#ifndef CTYPES_TYPES_H
#define CTYPES_TYPES_H
#include "ctypes_config.h"

#if CTYPES_HAVE_COMPLEX_H
#include <complex.h>
#endif

#if CTYPES_COMPLEX_STRUCTURE
#if defined(_WIN32) && defined(_MSC_VER)
typedef _Fcomplex ctypes_fcomplex;
typedef _Dcomplex ctypes_dcomplex;
typedef _Lcomplex ctypes_ldcomplex;
#else
typedef struct ctypes_fcomplex_ {
    float _Val[2];
} ctypes_fcomplex;

typedef struct ctypes_dcomplex_ {
    double _Val[2];
} ctypes_dcomplex;

typedef struct ctypes_ldcomplex_ {
    long double _Val[2];
} ctypes_ldcomplex;
#endif /* defined(_WIN32) && defined(_MSC_VER) */

#else
typedef float _Complex ctypes_fcomplex;
typedef double _Complex ctypes_dcomplex;
typedef long double _Complex ctypes_ldcomplex;

#endif /* CTYPES_COMPLEX_STRUCTURE */

#if CTYPES_POSIX_TYPES_ENABLED

#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <stdint.h>
#if !defined(_WIN32) || !defined(_MSC_VER)
#include <unistd.h>
#endif

typedef clock_t ctypes_clock_t;
typedef dev_t ctypes_dev_t;
typedef ino_t ctypes_ino_t;
typedef off_t ctypes_off_t;
typedef time_t ctypes_time_t;

#ifndef _WIN32
typedef nlink_t ctypes_nlink_t;
#else
/* The st_nlink field of struct [_]?stat(32|64)? is short. See msvc's
   header (sys/stats.h) (ucrt) or mingw's _stat */
typedef short ctypes_nlink_t;
#endif

#if !defined(_WIN32) || !defined(_MSC_VER)
typedef ssize_t ctypes_ssize_t;
typedef useconds_t ctypes_useconds_t;

#ifndef _WIN32
typedef mode_t ctypes_mode_t;
typedef pid_t ctypes_pid_t;
typedef sigset_t ctypes_sigset_t;
#else
typedef _mode_t ctypes_mode_t;
typedef _pid_t ctypes_pid_t;
typedef _sigset_t ctypes_sigset_t;
#endif

#else
/*
  The following types are not defined by msvc.
  Definitions provided by mingw-w64 in <sys/types.h>
  are used.
*/
#include <BaseTsd.h>
typedef SSIZE_T ctypes_ssize_t;
typedef unsigned int ctypes_useconds_t;
typedef unsigned short ctypes_mode_t;

#ifdef _WIN64
typedef __int64 ctypes_pid_t; /* dubious, but mingw's decision ... */
typedef unsigned long long ctypes_sigset_t;
#else
typedef int	ctypes_pid_t;
typedef unsigned long ctypes_sigset_t;
#endif

#endif /* !defined(_WIN32) || !defined(_MSC_VER) */

#endif /* CTYPES_POSIX_TYPES_ENABLED */

#endif /* CTYPES_TYPES_H */
