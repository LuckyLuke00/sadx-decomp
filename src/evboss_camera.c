#include "decls.h"

// STUB: SADX 0x0060d940
void EventBossCameraSet(struct task *bctp)
{
}

// STUB: SADX 0x0060e020
void FUN_0060e020(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2, struct NJS_POINT3 *param_3)
{
}

// FUNCTION: SADX 0x0060e1d0
float FUN_0060e1d0(float *param_1, float *param_2)
{
	float local_cg;
	float local_8g;

	local_cg = param_2[0] - param_1[0];
	local_8g = param_2[2] - param_1[2];
	local_cg = local_cg * local_cg + 0.0f + local_8g * local_8g;
	return njSqrt(local_cg);
}

// FUNCTION: SADX 0x0060e220
void NpcGetCameraPos(struct NJS_POINT3 *pos)
{
	*pos = *(struct NJS_POINT3 *)((char *)DAT_05b42a7c + 0x20);
}

// FUNCTION: SADX 0x0060e240
void EventBossCameraSetFunc()
{
	CameraSetEventCameraFunc(EventBossCamera, 0, 2);
}
