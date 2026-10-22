#include "decls.h"

// FUNCTION: SADX 0x005be280
void FUN_005be280(int param_1, int param_2)
{
	float local_8g;
	float local_cg;
	local_8g = *(float *)(param_2 + 0x130);
	local_cg = *(float *)(param_1 + 0x24) - local_8g;
	*(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x7c) / (local_cg * 1.4f + 3.0f) + *(float *)(param_2 + 0x14);
}
