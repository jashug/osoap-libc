#ifndef _OSOAP_SYSCALL_H
#define _OSOAP_SYSCALL_H

#include <sys/types.h>

_Noreturn void __osoap_exit_process(int);
_Noreturn void __osoap_exit_thread(void);

pid_t __osoap_gettid(void);
pid_t __osoap_getpid(void);
pid_t __osoap_getppid(void);

#endif
