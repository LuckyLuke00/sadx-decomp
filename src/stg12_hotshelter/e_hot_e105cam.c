#include "decls.h"
extern float DAT_060dd7b0;
extern float DAT_060dd7b4;
extern float DAT_060dd7b8;
extern long DAT_060dd7ac;
extern long DAT_060dd7a8;
extern long DAT_060dd7bc;
extern long DAT_060dd7c0;
void CameraSetEventCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect);
void CameraHotTgtDeath(struct _OBJ_CAMERAPARAM *pParam);

// FUNCTION: SADX 0x008b61f0
void CamHot_SetE105(struct task *pTask)
{
	CameraReleaseEventCamera();
}

// FUNCTION: SADX 0x008b6340
void StartCameraHot_TgtDeath(struct NJS_POINT3 *pPos, long angCenter, int time)
{
	DAT_060dd7b0 = pPos->x;
	DAT_060dd7c0 = 0;
	DAT_060dd7b4 = pPos->y;
	DAT_060dd7ac = time;
	DAT_060dd7b8 = pPos->z;
	DAT_060dd7a8 = angCenter + -0x5555;
	DAT_060dd7bc = 0xaaaa / time;
	CameraSetEventCameraFunc(CameraHotTgtDeath, 0, 2);
}
