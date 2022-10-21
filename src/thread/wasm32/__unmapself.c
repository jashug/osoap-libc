#include "pthread_impl.h"
#include "atomic.h"
#include "syscall.h"

void __unmapself(void *base, size_t size)
{
	__syscall(SYS_munmap, base, size);
	__syscall(SYS_exit);
}
