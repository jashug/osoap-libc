// #ifdef OSOAP_USE_FORK
typedef unsigned long __jmp_buf[4096 / sizeof(long) + 12];
// #else
// typedef unsigned long __jmp_buf[6];
// #endif
