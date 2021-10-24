#ifndef _OSOAP_SYSCALL_BUFFER_H
#define _OSOAP_SYSCALL_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

#define __OSOAP_SYS_TURN_USER 0
#define __OSOAP_SYS_TURN_KERNEL 1
#define __OSOAP_SYS_TURN_DETACHED 2
#define __OSOAP_SYS_FLAG_SIGNAL 0x1
#define __OSOAP_SYS_FLAG_DEBUGGER 0x2
#define __OSOAP_SYS_TAGW_linux_syscall 1
#define __OSOAP_SYS_TAGR_linux_syscall_return 2
#define __OSOAP_SYS_TAGW_poll_signals 3
#define __OSOAP_SYS_TAGR_signal_then_retry 4
#define __OSOAP_SYS_TAGW_exit_process 5

#define __OSOAP_SYS_TAGW_exit_thread 7

#define __OSOAP_SYS_TAGW_fork 9

struct __osoap_pathname {
	int rootfd;
	int curfd; // Ignored if path is absolute
	size_t pathlen;
	char *path;
};

struct __osoap_syscall_buffer {
	int32_t sync_state;
	uint32_t flag_word;
	uint32_t tag;
	uint32_t padding;
	union {
		struct {
			long n;
			uint32_t cnt;
			long long args[7];
		} linux_syscall;
		long long linux_syscall_return;
		int exit_process_code;
		struct {
			void *stack_buf;
			uint32_t saved_globals[15];
		} fork;
	} u;
};

uint32_t __osoap_send_syscall(struct __osoap_syscall_buffer *);
bool __osoap_send_syscall_restartable(struct __osoap_syscall_buffer *, uint32_t *);
void __osoap_process_signals_after_syscall(struct __osoap_syscall_buffer *, uint32_t *);
void __osoap_poll_signals(void);

__attribute__((import_module("diagnostic"), import_name("debugger")))
void __wasm_debugger(void);

__attribute__((import_name("throw_exit")))
_Noreturn void __wasm_throw_exit(void);

#endif
