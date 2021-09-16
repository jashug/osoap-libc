#ifndef _OSOAP_SYSCALL_H
#define _OSOAP_SYSCALL_H

#include <sys/types.h>

_Noreturn void __osoap_exit_process(int);
_Noreturn void __osoap_exit_thread(void);

pid_t __osoap_gettid(void);

struct __asyncify_stack {
	void *start, *end;
};

__attribute__((import_name("fork")))
pid_t __osoap_fork(struct __osoap_syscall_buffer *, struct __asyncify_stack *);

#endif
