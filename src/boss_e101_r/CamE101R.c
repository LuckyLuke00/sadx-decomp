#include "decls.h"
extern float DAT_060c4668;
extern int DAT_060c4634;
extern float DAT_060c4670;
extern int DAT_060c4660;
extern int DAT_060c4630;
extern float DAT_060c4664;
extern float DAT_060c466c;
extern int DAT_060c4658;
extern int DAT_060c4644;
extern float DAT_060c4678;

// FUNCTION: SADX 0x0070aa90
void CamE101R_Set()
{
	DAT_060c4670 = 20.0f;
	DAT_060c4660 = 0;
	DAT_060c4630 = 0;
	DAT_060c4664 = 23.0f;
	DAT_060c4644 = 0;
	DAT_060c4678 = 0.0f;
	DAT_060c466c = 0.0f;
}

// STUB: SADX 0x0070aad0
void CamE101R_SetPos(struct NJS_POINT3 *pPos)
{
}

// FUNCTION: SADX 0x0070ab50
void CamE101R_SetViewHeight(float fHeight)
{
	DAT_060c4678 = fHeight;
}

// FUNCTION: SADX 0x0070ab60
void CamE101R_SetPlayerSpd_Ang(float fSpd, long angTgt)
{
	DAT_060c4668 = fSpd;
	DAT_060c4634 = angTgt;
}

// FUNCTION: SADX 0x0070ab80
void CamE101R_SetMissileFlag(long flag)
{
	DAT_060c4644 = flag;
}

// FUNCTION: SADX 0x0070ab90
void CamE101R_SetMode(enum CAM_E101R_MODE mode)
{
	DAT_060c4630 = mode;
}

// FUNCTION: SADX 0x0070aba0
long CamE101R_GetAngleDist()
{
	long iVar1;
	iVar1 = SubAngle(DAT_060c4658, DAT_060c4634);
	if (iVar1 < 0) {
		iVar1 = SubAngle(DAT_060c4658, DAT_060c4634);
		return -iVar1;
	}
	iVar1 = SubAngle(DAT_060c4658, DAT_060c4634);
	return iVar1;
}

// FUNCTION: SADX 0x0070abf0
long CamE101R_GetAngle()
{
	return DAT_060c4658;
}

// STUB: SADX 0x0070b400
void CameraE101R(struct _OBJ_CAMERAPARAM *pParam)
{
}
