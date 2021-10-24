#ifndef _OSOAP_SYSCALL_H
#define _OSOAP_SYSCALL_H

#include <sys/types.h>

_Noreturn void __osoap_exit_process(int);
_Noreturn void __osoap_exit_thread(void);

#endif
