#include "osoap_syscall.h"
#include "pthread_impl.h"

pid_t __osoap_gettid()
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_gettid;
	uint32_t flags = __osoap_send_syscall(sys_buf);
	pid_t ret = sys_buf->u.pid_return;
	__osoap_process_signals_after_syscall(sys_buf, &flags);
}

pid_t __osoap_getpid()
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_getpid;
	uint32_t flags = __osoap_send_syscall(sys_buf);
	pid_t ret = sys_buf->u.pid_return;
	__osoap_process_signals_after_syscall(sys_buf, &flags);
}

pid_t __osoap_getppid()
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_getppid;
	uint32_t flags = __osoap_send_syscall(sys_buf);
	pid_t ret = sys_buf->u.pid_return;
	__osoap_process_signals_after_syscall(sys_buf, &flags);
}
