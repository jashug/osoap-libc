#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

// TODO: These definitions are stubs

// Call out to javascript to log syscalls when they are made
__attribute__((import_name("log_syscall")))
long __wasm_log_syscall(long n);

static __inline long __syscall0(long n) {
  return __wasm_log_syscall(n);
}

static __inline long __syscall1(long n, long a1) {
  return __wasm_log_syscall(n);
}

static __inline long __syscall2(long n, long a1, long a2) {
  return __wasm_log_syscall(n);
}

static __inline long __syscall3(long n, long a1, long a2, long a3) {
  return __wasm_log_syscall(n);
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4) {
  return __wasm_log_syscall(n);
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5) {
  return __wasm_log_syscall(n);
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
  return __wasm_log_syscall(n);
}

static __inline long __syscall7(long n, long a1, long a2, long a3, long a4, long a5, long a6, long a7) {
  return __wasm_log_syscall(n);
}
