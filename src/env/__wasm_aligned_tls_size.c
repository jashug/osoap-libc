#include "libc.h"

#define MIN_TLS_ALIGN 16

static size_t align_size(size_t size, size_t align)
{
	return size + ((-size) & (align - 1));
}

size_t __wasm_tls_align()
{
	size_t align = __builtin_wasm_tls_align();
	// Make sure pthread is aligned
	if (align < MIN_TLS_ALIGN) return MIN_TLS_ALIGN;
	else return align;
}

size_t __wasm_aligned_tls_size()
{
	return align_size(__builtin_wasm_tls_size(), __wasm_tls_align());
}
