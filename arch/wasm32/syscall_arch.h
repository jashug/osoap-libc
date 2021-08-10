#include <stdint.h>
#include "pthread_impl.h"
#include "osoap_syscall_buffer.h"

#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

// Call out to javascript to log syscalls when they are made
__attribute__((import_module("diagnostic"),import_name("log_syscall")))
long __wasm_log_syscall(long n);

__attribute__((import_module("diagnostic"), import_name("debugger")))
void __wasm_debugger();

// Invariant: sys_buf->sync_state == __OSOAP_SYS_TURN_USER outside this function
static void __osoap_send_syscall(struct __osoap_syscall_buffer *sys_buf) {
	int32_t *sync_state = &sys_buf->sync_state;
	// Transfer control to the kernal
	a_store(sync_state, __OSOAP_SYS_TURN_KERNAL);
	__wake(sync_state, 1, 1);
	// Wait for the kernal to reply
	__futexwait(sync_state, __OSOAP_SYS_TURN_KERNAL, 1);
	if (sys_buf->tag == __OSOAP_SYS_TAGR_debugger) {
		__wasm_debugger();
	} else if (sys_buf->tag == __OSOAP_SYS_TAGR_signal) {
		// TODO: handle signal interruption
	}
}

static __inline long __syscall0(long n)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 0;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}

static __inline long __syscall1(long n, long a1)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 1;
	sys_buf->u.linux_syscall.args[0] = a1;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 2;
	sys_buf->u.linux_syscall.args[0] = a1;
	sys_buf->u.linux_syscall.args[1] = a2;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 3;
	sys_buf->u.linux_syscall.args[0] = a1;
	sys_buf->u.linux_syscall.args[1] = a2;
	sys_buf->u.linux_syscall.args[2] = a3;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 4;
	sys_buf->u.linux_syscall.args[0] = a1;
	sys_buf->u.linux_syscall.args[1] = a2;
	sys_buf->u.linux_syscall.args[2] = a3;
	sys_buf->u.linux_syscall.args[3] = a4;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 5;
	sys_buf->u.linux_syscall.args[0] = a1;
	sys_buf->u.linux_syscall.args[1] = a2;
	sys_buf->u.linux_syscall.args[2] = a3;
	sys_buf->u.linux_syscall.args[3] = a4;
	sys_buf->u.linux_syscall.args[4] = a5;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 6;
	sys_buf->u.linux_syscall.args[0] = a1;
	sys_buf->u.linux_syscall.args[1] = a2;
	sys_buf->u.linux_syscall.args[2] = a3;
	sys_buf->u.linux_syscall.args[3] = a4;
	sys_buf->u.linux_syscall.args[4] = a5;
	sys_buf->u.linux_syscall.args[5] = a6;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}

static __inline long __syscall7(long n, long a1, long a2, long a3, long a4, long a5, long a6, long a7)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
	sys_buf->u.linux_syscall.n = 7;
	sys_buf->u.linux_syscall.args[0] = a1;
	sys_buf->u.linux_syscall.args[1] = a2;
	sys_buf->u.linux_syscall.args[2] = a3;
	sys_buf->u.linux_syscall.args[3] = a4;
	sys_buf->u.linux_syscall.args[4] = a5;
	sys_buf->u.linux_syscall.args[5] = a6;
	sys_buf->u.linux_syscall.args[6] = a7;
	__osoap_send_syscall(sys_buf);
	return sys_buf->u.linux_syscall_return;
}
