#include "decls.h"
extern float DAT_060cef24;
extern float DAT_060cef28;
extern float DAT_060cef2c;
extern long DAT_060cef34;
extern long DAT_060cef30;
extern long DAT_060cef20;
extern long DAT_060cef18;
extern float DAT_060cef1c;

// FUNCTION: SADX 0x00811220
void SetCameraWindy_TgtDeathExpSize(float fSize)
{
	DAT_060cef1c = fSize;
}

// FUNCTION: SADX 0x00811360
void StartCameraWindy_TgtDeath(struct NJS_POINT3 *pPos, long angCenter, int time)
{
	DAT_060cef24 = pPos->x;
	DAT_060cef34 = 0;
	DAT_060cef28 = pPos->y;
	DAT_060cef20 = time;
	DAT_060cef2c = pPos->z;
	DAT_060cef18 = angCenter + -0x238e;
	DAT_060cef1c = 0.0f;
	DAT_060cef30 = 0x471c / time;
	CameraSetEventCameraFunc(CameraWindyTgtDeath, 0, 2);
}
