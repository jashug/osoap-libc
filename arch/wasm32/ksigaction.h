#include <features.h>

struct k_sigaction {
	void (*handler)(int);
	unsigned long flags;
	unsigned mask[2];
};
