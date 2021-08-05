#include <stddef.h>
#include "libc.h"
#include "pthread_impl.h"

extern void __wasm_init_tls(void *mem);

static struct tls_module main_tls;

static void static_wasm_setup_tls()
{
	main_tls.image = NULL; /* unused */
	// We don't have an uninitialized section
	main_tls.len = main_tls.size = __wasm_aligned_tls_size();
	main_tls.align = __wasm_tls_align();
	// From the thread pointer, go back this much
	main_tls.offset = main_tls.size;

	libc.tls_cnt = 1;
	libc.tls_head = &main_tls;
	libc.tls_align = main_tls.align;
	// Does this need to be padded? I don't think so.
	libc.tls_size = main_tls.size + sizeof(struct pthread);

	// This requires malloc to work before thread pointer is set up
	void *mem = aligned_alloc(libc.tls_align, libc.tls_size);

	// The pthread sits right after the tls
	pthread_t td = (pthread_t)(mem + main_tls.size);
	td->dtv = &td->wasm_builtin_dtv;
	td->wasm_builtin_dtv[0] = 1;
	td->wasm_builtin_dtv[1] = (uintptr_t)mem;
	if (__builtin_wasm_tls_size()) {
		__wasm_init_tls(mem);
	}

	// Set up td
	td->self = td;
	libc.can_do_threads = 1;
	td->detach_state = DT_JOINABLE;
	td->tid = __syscall(SYS_set_tid_address, &__thread_list_lock);
	td->locale = &libc.global_locale;
	td->robust_list.head = &td->robust_list.head;
	td->sysinfo = __sysinfo;
	td->next = td->prev = td;
}

weak_alias(static_wasm_setup_tls, __wasm_setup_tls);
