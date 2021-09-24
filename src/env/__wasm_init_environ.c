#include <stddef.h>
#include <unistd.h>
#include "libc.h"

static char *wasm_static_env[] = {
	"TERM=xterm-256color",
	NULL
};
static void wasm_init_environ()
{
	// TODO: read this from the worker
	__environ = &wasm_static_env;
}

weak_alias(wasm_init_environ, __wasm_init_environ);
