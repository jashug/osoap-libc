extern void __wasm_setup_tls();
extern void __wasm_call_ctors(void);
extern int main(void);

__attribute__((export_name("_start")))
void _start(void)
{
	__wasm_setup_tls();

	// The linker synthesizes this to call constructors.
	__wasm_call_ctors();

	// Call `main` which will either be the application's zero-argument
	// `main` function or a libc routine which calls `__main_argc_argv`.
	int r = main();

	// TODO: report r as exit code
}
