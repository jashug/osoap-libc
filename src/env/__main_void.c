#include <stddef.h>

// If the user-provided main expects arguments, it gets renamed to:
int __main_argc_argv(int argc, char *argv[]);

__attribute__((weak))
int main(void)
{
	// TODO: retrieve arguments
	char *(argv[1]) = {NULL};
	return __main_argc_argv(0, argv);
}
