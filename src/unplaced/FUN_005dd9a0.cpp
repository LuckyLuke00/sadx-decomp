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
