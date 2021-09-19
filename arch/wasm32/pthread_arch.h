static uintptr_t __get_tp()
{
	return &local_pthread;
}

#define MC_PC pc
