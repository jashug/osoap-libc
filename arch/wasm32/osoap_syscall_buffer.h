#ifndef _OSOAP_SYSCALL_BUFFER_H
#define _OSOAP_SYSCALL_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define __OSOAP_SYS_TURN_USER 0
#define __OSOAP_SYS_TURN_KERNEL 1
#define __OSOAP_SYS_TURN_DETACHED 2
#define __OSOAP_SYS_FLAG_SIGNAL 0x1
#define __OSOAP_SYS_FLAG_DEBUGGER 0x2
#define __OSOAP_SYS_FLAG_EXIT 0x4
#define __OSOAP_SYS_TAGW_linux_syscall 1
#define __OSOAP_SYS_TAGR_linux_syscall_return 2
#define __OSOAP_SYS_TAGW_detach 3
#define __OSOAP_SYS_TAGR_unknown_syscall 4
#define __OSOAP_SYS_TAGW_poll_signals 5
#define __OSOAP_SYS_TAGR_signal_then_retry 6

struct __osoap_syscall_buffer {
	int32_t sync_state;
	uint32_t flag_word;
	uint32_t tag;
	uint32_t padding;
	union {
		struct {
			long n;
			long args[7];
			uint32_t cnt;
		} linux_syscall;
		long linux_syscall_return;
		int detach_exit_code;
	} u;
};

uint32_t __osoap_send_syscall(struct __osoap_syscall_buffer *);
bool __osoap_send_syscall_restartable(struct __osoap_syscall_buffer *, uint32_t *);

#endif
