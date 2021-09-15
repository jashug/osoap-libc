#include "osoap_syscall.h"
#include "pthread_impl.h"

void __osoap_exit_process(int ec)
{
	struct __osoap_syscall_buffer *sys_buf = &pthread_self()->sys_buf;
	sys_buf->tag = __OSOAP_SYS_TAGW_exit_process;
	sys_buf->u.exit_process_code = ec;
	__osoap_send_syscall(sys_buf);
	// Should always throw_exit before we get here, but just in case.
	__wasm_throw_exit();
}
