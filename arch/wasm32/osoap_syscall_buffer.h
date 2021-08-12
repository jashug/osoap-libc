#ifndef _OSOAP_SYSCALL_BUFFER_H
#define _OSOAP_SYSCALL_BUFFER_H

#include <stdint.h>

#define __OSOAP_SYS_TURN_USER 0
#define __OSOAP_SYS_TURN_KERNAL 1
#define __OSOAP_SYS_TAGW_linux_syscall 1
#define __OSOAP_SYS_TAGR_debugger 2
#define __OSOAP_SYS_TAGR_signal 3
#define __OSOAP_SYS_TAGR_linux_syscall_return 4

struct __osoap_syscall_buffer {
	int32_t sync_state;
	uint32_t tag;
	union {
		struct {
			long n;
			long args[7];
			uint32_t cnt;
		} linux_syscall;
		long linux_syscall_return;
	} u;
};

#endif
