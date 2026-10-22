#include "decls.h"
extern float DAT_05b42914;
extern float DAT_05b42918;
extern float DAT_05b4291c;
extern float DAT_05b42908;
extern float DAT_05b4290c;
extern float DAT_05b42910;

// FUNCTION: SADX 0x00484cb0
void CameraALRcam(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0xc) = DAT_05b42908;
	*(float *)((char *)camcont_wp + 0x10) = DAT_05b4290c;
	*(float *)((char *)camcont_wp + 0x14) = DAT_05b42910;
	*(int *)((char *)camcont_wp + 0x24) = DAT_05b42920.x;
	*(int *)((char *)camcont_wp + 0x28) = DAT_05b42920.y;
	*(int *)((char *)camcont_wp + 0x2c) = DAT_05b42920.z;
}

// FUNCTION: SADX 0x00484d10
void CameraALRlok(struct _OBJ_CAMERAPARAM *pParam)
{
	*(float *)((char *)camcont_wp + 0xc) = DAT_05b42908;
	*(float *)((char *)camcont_wp + 0x10) = DAT_05b4290c;
	*(float *)((char *)camcont_wp + 0x14) = DAT_05b42910;
	*(float *)((char *)camcont_wp + 0x18) = DAT_05b42914;
	*(float *)((char *)camcont_wp + 0x1c) = DAT_05b42918;
	*(float *)((char *)camcont_wp + 0x20) = DAT_05b4291c;
	*(int *)((char *)camcont_wp + 0x2c) = 0;
}

// FUNCTION: SADX 0x00484d80
void AlrCam_Ini(struct AlrCam *___this)
{
	___this->mode = 0;
	___this->old_mode = 0;
}

// FUNCTION: SADX 0x00484d90
int FUN_00484d90(struct AlrCam *param_1)
{
	return param_1->mode;
}

// FUNCTION: SADX 0x00484da0
void AlrCam_CheckAndRelease(struct AlrCam *___this)
{
	if (___this->flag & 1)
	{
		CameraReleaseEventCamera();
		___this->flag &= 0xfffe;
	}
}

// FUNCTION: SADX 0x004861e0
void AlrCam_ConstraintAroundAng(struct AlrCam *___this, long angle)
{
	___this->flag |= 4;
	___this->aim_angle = angle;
}
