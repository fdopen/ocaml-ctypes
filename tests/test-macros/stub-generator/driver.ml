(*
 * Copyright (c) 2014 Jeremy Yallop.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 *)

(* Stub generation driver for the macro tests. *)

let cheader = "
#if !defined(_WIN32) || !defined(_MSC_VER)
#include <tgmath.h>
#else
#include <math.h>
#define exp(a) (sizeof (a) == sizeof (float) ? expf(a) : exp(a))
#endif
"

let () = Tests_common.run ~cheader Sys.argv (module Functions.Stubs)
