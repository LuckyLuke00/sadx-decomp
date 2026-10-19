#include "decls.h"

extern struct __MYMEM_DATA *DAT_025d7b20;
void *FUN_004cb010(unsigned long param_1);

// FUNCTION: SADX 0x004cafa0
struct __MYMEM_DATA *MYMEM_HeapInit(struct __MYMEM_DATA *mem)
{
	if (mem == 0)
	{
		mem = (struct __MYMEM_DATA *)FUN_004cb010(8);
	}
	if (mem != 0)
	{
		*(void **)mem = 0;
		*(int *)((char *)mem + 4) = 0;
	}
	return mem;
}

// FUNCTION: SADX 0x004cafe0
struct __MYMEM_DATA *MYMEM_SelectHeap(struct __MYMEM_DATA *mem)
{
	struct __MYMEM_DATA *local_8;

	local_8 = DAT_025d7b20;
	if (mem != 0)
	{
		DAT_025d7b20 = mem;
	}
	return local_8;
}
