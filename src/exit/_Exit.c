#include <stdlib.h>
#include "syscall.h"

__attribute__((import_name("throw_exit")))
_Noreturn void __wasm_throw_exit(int);

_Noreturn void _Exit(int ec)
{
	// __syscall detatch
	__wasm_throw_exit(ec);
}
