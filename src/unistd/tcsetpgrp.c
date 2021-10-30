#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

int tcsetpgrp(int fd, pid_t pgrp)
{
	pid_t pgrp_int = pgrp;
	return ioctl(fd, TIOCSPGRP, &pgrp_int);
}
