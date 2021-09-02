#include <stdlib.h>
#include "osoap_syscall.h"

_Noreturn void _Exit(int ec)
{
	__osoap_exit_process(ec);
}
