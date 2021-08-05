#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s)
{
	int expected = t;
	__atomic_compare_exchange_n(p, &expected, s, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	return expected;
}

#define a_swap a_swap
static inline int a_swap(volatile int *p, int v)
{
	return __atomic_exchange_n(p, v, __ATOMIC_SEQ_CST);
}

#define a_fetch_add a_fetch_add
static inline int a_fetch_add(volatile int *p, int v)
{
	return __atomic_fetch_add(p, v, __ATOMIC_SEQ_CST);
}

#define a_fetch_and a_fetch_and
static inline int a_fetch_and(volatile int *p, int v)
{
	return __atomic_fetch_and(p, v, __ATOMIC_SEQ_CST);
}

#define a_fetch_or a_fetch_or
static inline int a_fetch_or(volatile int *p, int v)
{
	return __atomic_fetch_or(p, v, __ATOMIC_SEQ_CST);
}

#define a_and_64 a_and_64
static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	__atomic_fetch_and(p, v, __ATOMIC_SEQ_CST);
}

#define a_or_64 a_or_64
static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	__atomic_fetch_or(p, v, __ATOMIC_SEQ_CST);
}

#define a_store a_store
static inline void a_store(volatile int *p, int x)
{
	__atomic_store_n(p, x, __ATOMIC_SEQ_CST);
}

#define a_crash a_crash
static inline void a_crash()
{
	__builtin_trap();
}
