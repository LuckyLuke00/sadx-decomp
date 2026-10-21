#include "decls.h"
extern float DAT_060cf248;
extern int DAT_060cf258;
extern int DAT_060cf244;
extern float DAT_060cf24c;
extern float DAT_060cf250;
extern int DAT_060cf23c;
extern int DAT_060cf254;
extern float DAT_060cf240;

// FUNCTION: SADX 0x00838530
void SetCameraMountain_TgtDeathExpSize(float fSize)
{
	DAT_060cf240 = fSize;
}

// FUNCTION: SADX 0x00838670
void StartCameraMountain_TgtDeath(struct NJS_POINT3 *pPos, long angCenter, int time)
{
	DAT_060cf248 = pPos->x;
	DAT_060cf258 = 0;
	DAT_060cf24c = pPos->y;
	DAT_060cf244 = time;
	DAT_060cf250 = pPos->z;
	DAT_060cf23c = angCenter + -0x238e;
	DAT_060cf240 = 0.0f;
	DAT_060cf254 = 0x471c / time;
	CameraSetEventCameraFunc(CameraMountainTgtDeath, 0, 2);
}
