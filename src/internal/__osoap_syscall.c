#include <stdint.h>
#include <stdlib.h>
#include "pthread_impl.h"
#include "osoap_syscall.h"

static uint32_t __osoap_syscall_load_flags(uint32_t *flag_word) {
	uint32_t flags = __atomic_load_n(flag_word, __ATOMIC_SEQ_CST);
	if (flags & __OSOAP_SYS_FLAG_DEBUGGER) {
		// When the FLAG_DEBUGGER bit gets set, call the debugger,
		// then clear the flag.
		// We may lose calls to the debugger if they get stacked up,
		// but that should be OK.
		__wasm_debugger();
		__atomic_fetch_and(flag_word, ~__OSOAP_SYS_FLAG_DEBUGGER, __ATOMIC_SEQ_CST);
	}
	return flags;
}

// Invariant: sys_buf->sync_state == __OSOAP_SYS_TURN_USER outside this function
uint32_t __osoap_send_syscall(struct __osoap_syscall_buffer *sys_buf) {
	int32_t *sync_state = &sys_buf->sync_state;
	// Transfer control to the kernel
	int32_t current_state = __OSOAP_SYS_TURN_USER;
	bool success = __atomic_compare_exchange_n(sync_state, &current_state, __OSOAP_SYS_TURN_KERNEL, false /* no spurrious failures */, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	if (success) {
		// The sync_state was __OSOAP_SYS_TURN_USER, we have changed
		// it to __OSOAP_SYS_TURN_KERNEL, so wake up the kernel.
		__builtin_wasm_memory_atomic_notify(sync_state, 1);
		// Wait for kernel to reply
		__builtin_wasm_memory_atomic_wait32(sync_state, __OSOAP_SYS_TURN_KERNEL, -1);
		current_state = __atomic_load_n(sync_state, __ATOMIC_SEQ_CST);
	}
	if (current_state == __OSOAP_SYS_TURN_DETACHED) {
		// The kernel is no longer listening to this syscall buffer,
		// and requesting that we exit immediately.
		// It could also be __OSOAP_SYS_TURN_KERNEL, but that would
		// be a bug on our side; we should always be sleeping when
		// sync_state is __OSOAP_SYS_TURN_KERNEL.
		__wasm_throw_exit();
	} else if (current_state == __OSOAP_SYS_TURN_KERNEL) {
		// Something has gone wrong; we should only be woken up when
		// the sync_state is changed away from TURN_KERNEL.
		// I don't think that spurrious wakes are a possibility here.
		// Check if any uses of atomic_notify can get called on freed
		// memory that might have been reused for a syscall buffer.
		__wasm_debugger();
		__wasm_throw_exit();
	}
	return __osoap_syscall_load_flags(&sys_buf->flag_word);
}

// TODO: stub
static void __osoap_execute_signal(struct __osoap_syscall_buffer *sys_buf) {
}

// consider a version tuned for multi-value, where we return both
// flags and the continuation flag.
bool __osoap_send_syscall_restartable(struct __osoap_syscall_buffer *sys_buf, uint32_t *flags) {
	*flags = __osoap_send_syscall(sys_buf);
	if (sys_buf->tag == __OSOAP_SYS_TAGR_signal_then_retry) {
		__osoap_execute_signal(sys_buf);
		return true;
	} else {
		return false;
	}
}

/* Template for a restartable syscall.
 * return_type __osoap_syscall_name(parameters) {
 *   struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
 *   uint32_t flags;
 *   do {
 *     // Set up sys_buf
 *     sys_buf->tag = __OSOAP_SYS_TAGW_tag_name;
 *     sys_buf->u.syscall_name.arguments = parameters;
 *   } while (__osoap_send_syscall_restartable(sys_buf, &flags));
 *   return_type return_value = sys_buf->u.syscall_return.value;
 *   __osoap_process_signals_after_syscall(sys_buf, &flags);
 *   return return_value;
 * }
 *
 * For non-restartable syscalls, this can (but does not need to be) simplified.
 * return_type __osoap_syscall_name(parameters) {
 *   struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
 *   // Set up sys_buf
 *   sys_buf->tag = __OSOAP_SYS_TAGW_tag_name;
 *   sys_buf->us.syscall_name.arguments = parameters;
 *   uint32_t flags = __osoap_send_syscall(sys_buf);
 *   return_type return_value = sys_buf->u.syscall_return.value;
 *   __osoap_process_signals_after_syscall(sys_buf, &flags);
 *   return return_value;
 * }
 */

void __osoap_process_signals_after_syscall(struct __osoap_syscall_buffer *sys_buf, uint32_t *flags) {
	if (*flags & __OSOAP_SYS_FLAG_SIGNAL) {
		do {
			sys_buf->tag = __OSOAP_SYS_TAGW_poll_signals;
		} while (__osoap_send_syscall_restartable(sys_buf, flags));
	}
}

void __osoap_poll_signals()
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags = __osoap_syscall_load_flags(&sys_buf->flag_word);
	__osoap_process_signals_after_syscall(sys_buf, &flags);
}
