#include <errno.h>
#include "syscall.h"

long long __syscall_ret(unsigned long long r)
{
	if (r > -4096ULL) {
		errno = -r;
		return -1;
	}
	return r;
}
