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

// FUNCTION: SADX 0x005be2d0
void FUN_005be2d0(struct taskwk *param_1, struct enemywk *param_2)
{
	param_2->acc.x = -param_2->velo.x * 0.03999999910593033f + param_2->acc.x;
	param_2->acc.y = -param_2->velo.y * 0.03999999910593033f + param_2->acc.y;
	param_2->acc.z = -param_2->velo.z * 0.03999999910593033f + param_2->acc.z;
	param_2->velo.x += param_2->acc.x;
	param_2->velo.y = param_2->acc.y - 0.05999999865889549f + param_2->velo.y;
	param_2->velo.z += param_2->acc.z;
	param_1->pos.x += param_2->velo.x;
	param_1->pos.y += param_2->velo.y;
	param_1->pos.z += param_2->velo.z;
	param_2->acc.x = 0.0f;
	param_2->acc.y = 0.0f;
	param_2->acc.z = 0.0f;
}
