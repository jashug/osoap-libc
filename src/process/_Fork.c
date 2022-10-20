#include <unistd.h>
#include <signal.h>
#include "syscall.h"
#include "libc.h"
#include "lock.h"
#include "pthread_impl.h"
#include "aio_impl.h"

static void dummy(int x) { }
weak_alias(dummy, __aio_atfork);

struct __asyncify_stack {
	void *start, *end;
};

__attribute__((import_name("fork")))
hidden pid_t __osoap_fork(struct __osoap_syscall_buffer *, struct __asyncify_stack *);

static pid_t __really_fork(struct __osoap_syscall_buffer *sysbuf)
{
	size_t size = 1024;
	char stack_buffer[size];
	struct __asyncify_stack stack_buf;
	stack_buf.start = &stack_buffer[0];
	stack_buf.end = &stack_buffer[size];
	pid_t ret = __osoap_fork(sysbuf, &stack_buf);
	if (ret < 0 && ret > -4096) {
		errno = -ret;
		return -1;
	}
	return ret;
}

pid_t _Fork(void)
{
	pid_t ret;
	sigset_t set;
	__block_all_sigs(&set);
	__aio_atfork(-1);
	LOCK(__abort_lock);
	ret = __really_fork(&__pthread_self()->sys_buf);
	__osoap_poll_signals();
	if (!ret) {
		pthread_t self = __pthread_self();
		self->tid = __syscall(SYS_gettid);
		self->robust_list.off = 0;
		self->robust_list.pending = 0;
		self->next = self->prev = self;
		__thread_list_lock = 0;
		libc.threads_minus_1 = 0;
		if (libc.need_locks) libc.need_locks = -1;
	}
	UNLOCK(__abort_lock);
	__aio_atfork(!ret);
	__restore_sigs(&set);
	return __syscall_ret(ret);
}
