#include <stdint.h>
#include "atomic.h"
#include "osoap_syscall_buffer.h"

__attribute__((import_module("diagnostic"), import_name("debugger")))
void __wasm_debugger();

// Invariant: sys_buf->sync_state == __OSOAP_SYS_TURN_USER outside this function
void __osoap_send_syscall(struct __osoap_syscall_buffer *sys_buf) {
	int32_t *sync_state = &sys_buf->sync_state;
	// Transfer control to the kernel
	a_store(sync_state, __OSOAP_SYS_TURN_KERNEL);
	__builtin_wasm_memory_atomic_notify(sync_state, 1);
	// Wait for kernel to reply
	__builtin_wasm_memory_atomic_wait32(sync_state, __OSOAP_SYS_TURN_KERNEL, -1);
}

// This function may clobber the syscall_buffer, so you should save
// the return value of previous syscalls before calling this function.
void __osoap_process_syscall_flags(struct __osoap_syscall_buffer *sys_buf) {
	uint32_t *flag_word = &sys_buf->flag_word;
	uint32_t flags;
	while ((flags = a_load(flag_word)) & __OSOAP_SYS_FLAG_SIGNAL) {
		// TODO: handle signals
		// This will look something like:
		// osoap_sig_descr signal = __syscall(SYS_poll_signal);
		// execute signal
		//
		// (The SYS_poll_signal returns one pending signal, and sets
		//  the FLAG_SIGNAL bit based on whether there are more signals
		//  after the returned one)
		// The FLAG_SIGNAL bit can also be set atomically any time by
		// the kernal, so if the signal handler makes system calls that
		// result in another signal being generated, we can stay in this
		// loop.
	}
	if (flags & __OSOAP_SYS_FLAG_DEBUGGER) {
		// When the FLAG_DEBUGGER bit gets set, call the debugger,
		// then clear the flag.
		// We may lose calls to the debugger if they get stacked up,
		// but that should be OK.
		__wasm_debugger();
		a_and(flag_word, ~__OSOAP_SYS_FLAG_DEBUGGER);
	}
}
