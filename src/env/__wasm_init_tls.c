#include <stddef.h>
#include "libc.h"
#include "pthread_impl.h"
#include "syscall.h"

extern void __wasm_init_tls(void *mem);

// Returns the thread id
// Pass in a pointer to write the thread id to on exit
// (superseeds SYS_set_tid_address)
__attribute__((import_name("register_syscall_buffer")))
int __wasm_register_sys_buf(struct __osoap_syscall_buffer *sys_buf, int *loc);

static struct tls_module main_tls;

__thread struct pthread local_pthread;

static void static_wasm_setup_tls()
{
	main_tls.image = NULL; /* unused */
	// We don't have an uninitialized section
	main_tls.len = main_tls.size = __builtin_wasm_tls_size();
	main_tls.align = __builtin_wasm_tls_align();
	// From the thread pointer, go back this much
	main_tls.offset = main_tls.size;

	libc.tls_cnt = 1;
	libc.tls_head = &main_tls;
	libc.tls_align = main_tls.align;
	// Does this need to be padded? I don't think so.
	libc.tls_size = main_tls.size;

	// This requires malloc to work before thread pointer is set up
	void *mem = aligned_alloc(libc.tls_align, libc.tls_size);
	if (!mem) __builtin_trap();

	if (!__builtin_wasm_tls_size()) __builtin_trap();
	__wasm_init_tls(mem);

	// Set up td
	pthread_t td = &local_pthread;
	memset(td, 0, sizeof(struct pthread));
	td->dtv = &td->wasm_builtin_dtv;
	td->wasm_builtin_dtv[0] = 1;
	td->wasm_builtin_dtv[1] = (uintptr_t)mem;
	td->self = td;
	libc.can_do_threads = 1;
	td->detach_state = DT_JOINABLE;
	td->tid = __wasm_register_sys_buf(&td->sys_buf, &__thread_list_lock);
	td->locale = &libc.global_locale;
	td->robust_list.head = &td->robust_list.head;
	td->sysinfo = __sysinfo;
	td->next = td->prev = td;
}

weak_alias(static_wasm_setup_tls, __wasm_setup_tls);
