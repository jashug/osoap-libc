#ifndef _OSOAP_SYSCALL_H
#define _OSOAP_SYSCALL_H

#include "osoap_syscall_buffer.h"

__attribute__((import_module("diagnostic"), import_name("debugger")))
void __wasm_debugger(void);

__attribute__((import_name("throw_exit")))
_Noreturn void __wasm_throw_exit(void);

void __osoap_poll_signals(void);
void __osoap_maybe_poll_signals(void);
_Noreturn void __osoap_exit_process(int);
_Noreturn void __osoap_exit_thread(void);

#endif
