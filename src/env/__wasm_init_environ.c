#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "libc.h"

__attribute__((import_name("environment_size")))
size_t __wasm_environment_size(void);
__attribute__((import_name("fill_environment")))
void __wasm_fill_environment(void *);

static void wasm_init_environ()
{
	__environ = malloc(__wasm_environment_size());
	if (__environ) __wasm_fill_environment(__environ);
}

weak_alias(wasm_init_environ, __wasm_init_environ);
