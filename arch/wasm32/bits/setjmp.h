#include <stddef.h>

struct __asyncify_stack {
	void *start, *end;
};

void __set_default_asyncify_buffer_size(size_t);
size_t __get_default_asyncify_buffer_size(void);

struct __jmp_buf {
	struct __asyncify_stack async_piece;
	void *unwound;
	char stack_buffer[4096];
};
typedef struct __jmp_buf __jmp_buf;
