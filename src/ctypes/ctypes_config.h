/*
 * Copyright (c) 2018 fdopen.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 */

#ifndef CTYPES_CONFIG_H
#define CTYPES_CONFIG_H

#if defined(__ANDROID__) && (!defined(__ANDROID_API__) || __ANDROID_API__ < 21)
#define CTYPES_HAVE_COMPLEX_H 0
#else
#define CTYPES_HAVE_COMPLEX_H 1
#endif

#if defined(__FreeBSD__) || ( defined(__ANDROID__) && (!defined(__ANDROID_API__) || __ANDROID_API__ < 26) )
#define CTYPES_HAVE_CEXPL 0
#define CTYPES_HAVE_CLOGL 0
#define CTYPES_HAVE_CPOWL 0
#else
#define CTYPES_HAVE_CEXPL 1
#define CTYPES_HAVE_CLOGL 1
#define CTYPES_HAVE_CPOWL 1
#endif

#ifdef __NetBSD__
#define CTYPES_HAVE_EXPM1L 0
#define CTYPES_HAVE_LOG1PL 0
#define CTYPES_HAVE_REMAINDERL 0
#else
#define CTYPES_HAVE_EXPM1L 1
#define CTYPES_HAVE_LOG1PL 1
#define CTYPES_HAVE_REMAINDERL 1
#endif

#define CTYPES_HAVE_CSQRTL 1
#define CTYPES_HAVE_CONJL 1
#define CTYPES_HAVE_CARGL 1

/* Manual inclusion of alloca.h is not necessary for most systems. */
#define CTYPES_HAVE_ALLOCA_H 0

#if defined(_WIN32) && defined(_MSC_VER)
#define CTYPES_COMPLEX_STRUCTURE 1
#else
#define CTYPES_COMPLEX_STRUCTURE 0
#endif

/* PosixTypes pull in many headers that are not fully portable. It can
   therefore be overriden during stub generation or by default.
   However, ctypes still depend on these headers internally, PosixTypes is
   not an optional dependency. */
#ifndef CTYPES_POSIX_TYPES_ENABLED
#define CTYPES_POSIX_TYPES_ENABLED 1
#endif

#endif /* CTYPES_CONFIG_H */
