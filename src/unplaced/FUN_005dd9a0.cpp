#include "decls.h"

// FUNCTION: SADX 0x005dd9a0
void FUN_005dd9a0(void *param_1)
{
	*(float *)((char *)param_1 + 0x34) = *(float *)((char *)param_1 + 0x34) + 0.10999999940395355;
	if (5.0 <= *(float *)((char *)param_1 + 0x34))
	{
		*(char *)param_1 = 2;
		*(float *)((char *)param_1 + 0x34) = 1.0;
	}
}

// STUB: SADX 0x005ddc80
void FUN_005ddc80(struct task *param_1)
{
}

// STUB: SADX 0x005ddea0
void FUN_005ddea0(struct task *param_1)
{
}
