#include "decls.h"

// FUNCTION: SADX 0x00595d50
void FUN_00595d50(int param_1, int param_2, int param_3)
{
	float local_8;

	local_8 = njSin(*(int *)((char *)param_2 + 0x1a4));
	*(float *)((char *)param_1 + 0x20) = *(float *)((char *)param_1 + 0x2c) * local_8 + *(float *)((char *)param_2 + 0x50);
	*(float *)((char *)param_1 + 0x24) = *(float *)((char *)param_1 + 0x30) * local_8 + *(float *)((char *)param_2 + 0x54);
	*(float *)((char *)param_1 + 0x28) = *(float *)((char *)param_1 + 0x34) * local_8 + *(float *)((char *)param_2 + 0x58);
	*(int *)((char *)param_2 + 0x1a4) = *(int *)((char *)param_2 + 0x1a4) + *(int *)((char *)param_1 + 0x1c);
}
