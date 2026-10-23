#include "decls.h"
long FUN_005c1c80(struct taskwk *param_1, struct enemywk *param_2);

// FUNCTION: SADX 0x005c1c80
long FUN_005c1c80(struct taskwk *param_1, struct enemywk *param_2)
{
	return FUN_005e3d10(param_1, param_2);
}

// FUNCTION: SADX 0x005c1ca0
void FUN_005c1ca0(int param_1, int param_2)
{
	float fVar1;
	float fVar2;
	fVar2 = 0.1f;
	fVar1 = 0.0f;
	*(float *)(param_2 + 0x10) += njCos(*(int *)(param_1 + 0x18)) * fVar2 + njSin(*(int *)(param_1 + 0x18)) * fVar1;
	*(float *)(param_2 + 0x18) += njSin(-*(int *)(param_1 + 0x18)) * fVar2 + njCos(*(int *)(param_1 + 0x18)) * fVar1;
}
