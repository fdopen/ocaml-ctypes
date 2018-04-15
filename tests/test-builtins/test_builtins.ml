(*
 * Copyright (c) 2013 Jeremy Yallop.
 *
 * This file is distributed under the terms of the MIT License.
 * See the file LICENSE for details.
 *)

open OUnit2
open Ctypes

module Bindings = Functions.Stubs(Generated_bindings)

(*
  Test calling builtins.
*)
let test_calling_builtins _ =
  let open Unsigned.UInt8 in
  let open Bindings in
  let u1 = of_int 0x77
  and u2 = of_int 0x8 in
  (* __sync_or_and_fetch and _InterlockedAnd8 differ slightly *)
  let expected1 = Infix.(u1 lor u2) in
  let expected2 = if Tests_common.is_msvc then u1 else expected1 in

  let p = allocate uint8_t u1 in
  assert (__sync_or_and_fetch p u2 = expected2);
  assert (!@p = expected1);

  p <-@ u1;
  assert (__sync_fetch_and_and p u2 = u1);
  assert (!@p = Infix.(u1 land u2))

let suite = "Builtin tests" >:::
  ["calling builtins"
    >:: test_calling_builtins;
  ]



let _ =
  run_test_tt_main suite
