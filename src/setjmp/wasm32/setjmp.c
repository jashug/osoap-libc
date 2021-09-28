/*
 * Copyright 2020 The Emscripten Authors
 * Modified by Jasper Hugunin.
 * Under MIT license.
 */
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>

// 0 - Nothing thrown
// 1 - Exception thrown
// Other values - jmpbuf pointer in the case that longjmp was thrown
static uintptr_t setjmpId = 0;

typedef struct TableEntry {
  uintptr_t id;
  uint32_t label;
} TableEntry;

static uint32_t __TempRet0;

static void __setTempRet0(uint32_t value)
{
	__TempRet0 = value;
}
weak_alias(__setTempRet0, setTempRet0);

uint32_t __getTempRet0(void)
{
	return __TempRet0;
}
weak_alias(__getTempRet0, getTempRet0);

static TableEntry* __saveSetjmp(uintptr_t* env, uint32_t label, TableEntry* table, uint32_t size) {
  // Not particularly fast: slow table lookup of setjmpId to label. But setjmp
  // prevents relooping anyhow, so slowness is to be expected. And typical case
  // is 1 setjmp per invocation, or less.
  uint32_t i = 0;
  setjmpId++;
  *env = setjmpId;
  while (i < size) {
    if (table[i].id == 0) {
      table[i].id = setjmpId;
      table[i].label = label;
      // prepare next slot
      table[i + 1].id = 0;
      setTempRet0(size);
      return table;
    }
    i++;
  }
  // grow the table
  size *= 2;
  table = (TableEntry*)realloc(table, sizeof(TableEntry) * (size +1));
  table = __saveSetjmp(env, label, table, size);
  setTempRet0(size); // FIXME: unneeded?
  return table;
}
weak_alias(__saveSetjmp, saveSetjmp);

uint32_t __testSetjmp(uintptr_t id, TableEntry* table, uint32_t size) {
  uint32_t i = 0;
  while (i < size) {
    uintptr_t curr = table[i].id;
    if (curr == 0) break;
    if (curr == id) {
      return table[i].label;
    }
    i++;
  }
  return 0;
}
weak_alias(__testSetjmp, testSetjmp);

struct __WasmLongjmpArgs {
  void *env;
  int val;
};
struct __WasmLongjmpArgs __wasm_longjmp_args;

void __wasm_longjmp(void *env, int val)
{
	__wasm_longjmp_args.env = env;
	__wasm_longjmp_args.val = val;
	__builtin_wasm_throw(1, &__wasm_longjmp_args);
}
