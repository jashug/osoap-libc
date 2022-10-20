/*
 * Copyright 2020 Jasper Hugunin
 * Under MIT license.
 */
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>

extern hidden size_t __default_async_buffer_size;

__attribute__((import_name("setjmp")))
hidden int __osoap_setjmp(__jmp_buf *);
__attribute__((import_name("longjmp")))
hidden int __osoap_longjmp(struct __asyncify_stack *, struct __asyncify_stack *, int);

int setjmp(jmp_buf buf)
{
	buf->__jb.async_piece.start = &buf->__jb.stack_buffer[0];
	buf->__jb.async_piece.end = &buf->__jb.stack_buffer[sizeof(buf->__jb.stack_buffer) / sizeof(buf->__jb.stack_buffer[0])];
	return __osoap_setjmp(&buf->__jb);
}

void longjmp(jmp_buf buf, int value)
{
	size_t size = 1024;
	char stack_buffer[size];
	struct __asyncify_stack stack_buf;
	stack_buf.start = &stack_buffer[0];
	stack_buf.end = &stack_buffer[size];
	buf->__jb.async_piece.start = buf->__jb.unwound;
	__osoap_longjmp(&stack_buf, &buf->__jb.async_piece, value);
}
