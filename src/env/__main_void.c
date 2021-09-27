#include <stddef.h>
#include <stdlib.h>

// If the user-provided main expects arguments, it gets renamed to:
int __main_argc_argv(int argc, char *argv[]);

__attribute__((import_name("argv_size")))
size_t __wasm_argv_size(void);
__attribute__((import_name("fill_argv")))
int __wasm_fill_argv(char **);

static int static_main(void)
{
	// TODO: retrieve arguments
	char **argv = malloc(__wasm_argv_size());
	if (!argv) return 1;
	int argc = __wasm_fill_argv(argv);
	return __main_argc_argv(argc, argv);
}

weak_alias(static_main, __main_void);
