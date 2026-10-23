#include "decls.h"

// FUNCTION: SADX 0x0055e510
void FUN_0055e510(void *param_1)
{
	if (param_1 != NULL)
	{
		Free(*(void **)((char *)param_1 + 0x10));
		Free(param_1);
	}
}

// STUB: SADX 0x0055ea20
void FUN_0055ea20(void *param_1)
{
}

// STUB: SADX 0x0055eaf0
int FUN_0055eaf0(void *param_1)
{
	return (int)0;
}

// STUB: SADX 0x0055f0c0
void hintbox_end(struct task *task_p)
{
}
