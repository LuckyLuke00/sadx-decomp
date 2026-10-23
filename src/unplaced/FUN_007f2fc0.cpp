#include "decls.h"
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);

// FUNCTION: SADX 0x007f2fc0
void FUN_007f2fc0(struct task *param_1)
{
	if (*(void **)param_1->awp != NULL)
	{
		Free(*(void **)param_1->awp);
		*(void **)param_1->awp = NULL;
	}
}

// FUNCTION: SADX 0x007f2ff0
void *FUN_007f2ff0()
{
	void *var1;
	var1 = MAlloc(0x198);
	memset(var1, 0, 0x198);
	return var1;
}
