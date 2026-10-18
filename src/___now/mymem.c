#include "decls.h"

extern struct __MYMEM_DATA *DAT_025d7b20;
void *FUN_004cb010(unsigned long param_1);

// FUNCTION: SADX 0x004cafa0
struct __MYMEM_DATA *MYMEM_HeapInit(struct __MYMEM_DATA *param_1)
{
	if (param_1 == 0)
	{
		param_1 = (struct __MYMEM_DATA *)FUN_004cb010(8);
	}
	if (param_1 != 0)
	{
		*(void **)param_1 = 0;
		*(int *)((char *)param_1 + 4) = 0;
	}
	return param_1;
}

// FUNCTION: SADX 0x004cafe0
struct __MYMEM_DATA *MYMEM_SelectHeap(struct __MYMEM_DATA *param_1)
{
	struct __MYMEM_DATA *old;

	old = DAT_025d7b20;
	if (param_1 != 0)
	{
		DAT_025d7b20 = param_1;
	}
	return old;
}
