#include <unistd.h>
#include "syscall.h"

pid_t getpid(void)
{
	return __osoap_getpid();
}
