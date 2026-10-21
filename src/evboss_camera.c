#include "decls.h"

// STUB: SADX 0x0060e1d0
float FUN_0060e1d0(float *param_1, float *param_2)
{
	return (float)0;
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
