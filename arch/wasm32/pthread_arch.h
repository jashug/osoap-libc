static inline uintptr_t __get_tp() {
  return __builtin_wasm_tls_base();
}

#define MC_PC pc
