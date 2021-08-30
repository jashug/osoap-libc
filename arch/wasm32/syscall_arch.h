#include <stdint.h>
#include "pthread_impl.h"
#include "osoap_syscall_buffer.h"

#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

static __inline long __syscall0(long n)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 0;
		sys_buf->u.linux_syscall.n = n;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	uint32_t flags;
	do {
		sys_buf->tag = __OSOAP_SYS_TAGW_linux_syscall;
		sys_buf->u.linux_syscall.cnt = 1;
		sys_buf->u.linux_syscall.n = n;
		sys_buf->u.linux_syscall.args[0] = a1;
	} while (__osoap_send_syscall_restartable(sys_buf, &flags));
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
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
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
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
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
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
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
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
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
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
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}

static __inline long __syscall7(long n, long a1, long a2, long a3, long a4, long a5, long a6, long a7)
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
	long ret = sys_buf->u.linux_syscall_return;
	if (flags & __OSOAP_SYS_FLAG_SIGNAL) {
		__osoap_poll_signals();
	}
	return ret;
}
