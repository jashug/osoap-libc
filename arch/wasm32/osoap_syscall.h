#ifndef _OSOAP_SYSCALL_H
#define _OSOAP_SYSCALL_H

#include "osoap_syscall_buffer.h"

__attribute__((import_module("diagnostic"), import_name("debugger")))
void __wasm_debugger();

__attribute__((import_name("throw_exit")))
_Noreturn void __wasm_throw_exit();

void __osoap_detach(int);

#endif
