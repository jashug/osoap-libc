#include <stdint.h>
#include "pthread_impl.h"
#include "osoap_syscall.h"

#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

typedef long long syscall_arg_t;
typedef long long syscall_ret_t;

static __inline syscall_ret_t __syscall0(syscall_arg_t n)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 0;
		sys_buf->u.linux_syscall.n = n;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline syscall_ret_t __syscall1(syscall_arg_t n, syscall_arg_t a1)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 1;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline syscall_ret_t __syscall2(syscall_arg_t n, syscall_arg_t a1, syscall_arg_t a2)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 2;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
		sys_buf->u.linux_syscall.args[1] = a2;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline syscall_ret_t __syscall3(syscall_arg_t n, syscall_arg_t a1, syscall_arg_t a2, syscall_arg_t a3)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 3;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
		sys_buf->u.linux_syscall.args[1] = a2;
		sys_buf->u.linux_syscall.args[2] = a3;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline syscall_ret_t __syscall4(syscall_arg_t n, syscall_arg_t a1, syscall_arg_t a2, syscall_arg_t a3, syscall_arg_t a4)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 4;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
		sys_buf->u.linux_syscall.args[1] = a2;
		sys_buf->u.linux_syscall.args[2] = a3;
		sys_buf->u.linux_syscall.args[3] = a4;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline syscall_ret_t __syscall5(syscall_arg_t n, syscall_arg_t a1, syscall_arg_t a2, syscall_arg_t a3, syscall_arg_t a4, syscall_arg_t a5)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 5;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
		sys_buf->u.linux_syscall.args[1] = a2;
		sys_buf->u.linux_syscall.args[2] = a3;
		sys_buf->u.linux_syscall.args[3] = a4;
		sys_buf->u.linux_syscall.args[4] = a5;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline syscall_ret_t __syscall6(syscall_arg_t n, syscall_arg_t a1, syscall_arg_t a2, syscall_arg_t a3, syscall_arg_t a4, syscall_arg_t a5, syscall_arg_t a6)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 6;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
		sys_buf->u.linux_syscall.args[1] = a2;
		sys_buf->u.linux_syscall.args[2] = a3;
		sys_buf->u.linux_syscall.args[3] = a4;
		sys_buf->u.linux_syscall.args[4] = a5;
		sys_buf->u.linux_syscall.args[5] = a6;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline syscall_ret_t __syscall7(syscall_arg_t n, syscall_arg_t a1, syscall_arg_t a2, syscall_arg_t a3, syscall_arg_t a4, syscall_arg_t a5, syscall_arg_t a6, syscall_arg_t a7)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 7;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
		sys_buf->u.linux_syscall.args[1] = a2;
		sys_buf->u.linux_syscall.args[2] = a3;
		sys_buf->u.linux_syscall.args[3] = a4;
		sys_buf->u.linux_syscall.args[4] = a5;
		sys_buf->u.linux_syscall.args[5] = a6;
		sys_buf->u.linux_syscall.args[6] = a7;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	syscall_ret_t ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}
