static uintptr_t __get_tp()
{
	return __builtin_wasm_tls_base() + __wasm_aligned_tls_size();
}

#define MC_PC pc
