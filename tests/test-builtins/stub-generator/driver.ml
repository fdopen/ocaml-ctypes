(*
 * Copyright (c) 2014 Jeremy Yallop.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 *)

(* Stub generation driver for the builtins tests. *)

let cheader = "
#if defined(_WIN32) && defined(_MSC_VER)
#include <intrin.h>
#define  __sync_or_and_fetch(a,b) _InterlockedOr8((volatile char*)a,(long)(b))
#define __sync_fetch_and_and _InterlockedAnd8
#endif
"

let () = Tests_common.run ~cheader Sys.argv (module Functions.Stubs)
