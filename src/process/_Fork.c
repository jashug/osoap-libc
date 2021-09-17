#include <unistd.h>
#include <signal.h>
#include "syscall.h"
#include "libc.h"
#include "lock.h"
#include "pthread_impl.h"
#include "aio_impl.h"

static void dummy(int x) { }
weak_alias(dummy, __aio_atfork);

size_t osoap_fork_stack_size = 1024; // bytes

void __osoap_set_fork_stack_size(size_t size)
{
	osoap_fork_stack_size = size;
}

pid_t _Fork(void)
{
	pid_t ret;
	sigset_t set;
	__block_all_sigs(&set);
	__aio_atfork(-1);
	LOCK(__abort_lock);
	int stack_buffer[osoap_fork_stack_size >> 2];
	struct __asyncify_stack stack_buf;
	stack_buf.start = (void *)&stack_buffer;
	stack_buf.end = ((void *)&stack_buffer) + sizeof(stack_buffer);
	ret = __syscall_ret(__osoap_fork(&__pthread_self()->sys_buf, &stack_buf));
	__osoap_poll_signals();
	if (!ret) {
		pthread_t self = __pthread_self();
		self->tid = __osoap_gettid();
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
