#include "decls.h"
extern float DAT_060bd164;
extern int DAT_060bd14c;
extern float DAT_060bd178;

// STUB: SADX 0x006e01b0
void CamRobo_SetPos(struct NJS_POINT3 *pPos)
{
}

// FUNCTION: SADX 0x006e0230
void CamRobo_SetExpSize(float fSize)
{
	DAT_060bd178 = fSize;
}

// FUNCTION: SADX 0x006e0240
void CamRobo_SetMode(enum CAM_ROBO_MODE mode)
{
	DAT_060bd14c = mode;
	if (mode == 5)
	{
		DAT_060bd164 = 0.7f;
		DAT_060bd178 = 0.0f;
	}
}

// STUB: SADX 0x006e0950
void CameraRobo(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x006e09b0
void CamRobo_Set()
{
}
