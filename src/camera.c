#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern float DAT_05b42828;
extern float DAT_05b4282c;
long FUN_004bf650(float *param_1, float *param_2);
long addcolCube(struct _OBJ_CAMERAENTRY *entry, struct NJS_POINT3 *pos);
extern int DAT_05b4259c;
extern struct NJS_CACTION *DAT_05b425cc;
extern float DAT_05b4293c;
void FUN_005b5aa0(...);
extern int DAT_05b42a88;
extern double DAT_0095cbf8;
extern int DAT_05b42990;
void CameraReleaseCollisionCamera();
extern struct _OBJ_ADJUSTPARAM *pObjAdjustParam;
extern float DAT_05b429a8;
extern float DAT_05b429ac;
extern float DAT_05b429b0;
extern float DAT_05b429b4;
extern float DAT_05b429b8;
extern float DAT_05b429bc;
extern short DAT_05b429a4;
extern short DAT_05b429a6;
extern float DAT_05b429c0;
extern int DAT_05b429c4;
extern struct _camcontwk *camcont_wp;
extern int DAT_05b42940;
extern short DAT_05b4294a;
extern char DAT_05b42948;
extern char DAT_05b4294c;
extern char DAT_05b4294d;
extern int DAT_05b42950;
extern char DAT_05b42954;
extern int DAT_05b42958;
extern int DAT_05b425c8;
extern NJS_POINT3 DAT_05b425d0[0x32];
extern float DAT_05b4289c;
extern float DAT_05b428a0;
extern float DAT_05b428a4;
extern struct NJS_POINT3 DAT_05b4295c;
extern struct taskwk *DAT_05baf368[8];
extern int DAT_05b4299c[1];
extern int *DAT_05b4298c;
extern int DAT_05b42a74;
extern int DAT_05b42860;
void FUN_004bee10(void);
void SetAdjustMode(long AdjustType);
extern struct _CameraSystemWork *pCameraSystemWork;
extern short DAT_05b42998;
extern int DAT_05b42894;
extern int DAT_05b42974;
extern int DAT_05b428e8;
extern unsigned long DAT_05cda1b0;
extern struct taskwk *DAT_05b42a7c;
extern int DAT_05b42a80;
extern int DAT_05b42a78;
extern int DAT_05b42994;
extern unsigned long DAT_05b429a0;
extern int DAT_05b42968;

extern int DAT_05b42978;

// FUNCTION: SADX 0x004bade0
void SetStartCameraMode(signed char mode)
{
	DAT_05b42978 = mode;
}

// FUNCTION: SADX 0x004badf0
void SetDefaultNormalCameraMode(signed char mode, signed char adjust)
{
	DAT_05b42a78 = mode;
	DAT_05b42994 = adjust;
}

// FUNCTION: SADX 0x004bae10
long GetViewAngle()
{
	return DAT_05b42968;
}

// FUNCTION: SADX 0x004bae20
void SetViewAngle(long new_view_angle)
{
	switch (*(signed char *)((char *)pCameraSystemWork + 0x6))
	{
	case 0x1c:
	case 0x1d:
	case 0x1e:
		if (GetAdjustMode())
		{
			DAT_05b42968 = AdjustAngle(DAT_05b42968, 0x31c7, 0x12);
		}
		else
		{
			DAT_05b42968 = 0x31c7;
		}
		break;
	default:
		DAT_05b42968 = new_view_angle;
		break;
	}
	___njSetPerspective(DAT_05b42968);
	DAT_05b42a80 = DAT_05b42968;
}

// STUB: SADX 0x004baea0
void SetCameraTask()
{
}

// FUNCTION: SADX 0x004bafb0
void FUN_004bafb0(void)
{
	DAT_05b42968 = 0x31c7;
	___njSetPerspective(DAT_05b42968);
	DAT_05b42a80 = DAT_05b42968;
}

// STUB: SADX 0x004bafe0
void cameraModeInit()
{
}

// FUNCTION: SADX 0x004bb090
void CameraEnd(struct task *pTask)
{
	DAT_05b42a7c = 0;
}

// FUNCTION: SADX 0x004bb0a0
void CameraPause(struct task *pTask)
{
	struct taskwk *local_8;
	local_8 = pTask->twp;
	CameraViewSet(local_8);
}

// FUNCTION: SADX 0x004bb0c0
void AddCameraStage(short ssStep)
{
	if (ChkGameMode() == 0)
	{
		return;
	}
	DAT_05b42998 += ssStep;
	DAT_05b42894 = ((unsigned long *)&DAT_05cda1b0)[DAT_05b42998];
	DAT_05b42974 = ((unsigned long *)&DAT_05cda1b0)[DAT_05b42998] + 0x40;
	cameraModeInit();
	DAT_05b429a0 = 0;
	DAT_05b428e8 = 0;
}

// STUB: SADX 0x004bb340
void FUN_004bb340()
{
}

// STUB: SADX 0x004bb4f0
void CameraManager()
{
}

// STUB: SADX 0x004bb800
long CameraCollisionShpere(struct _OBJ_CAMERAENTRY *pCameraEntry)
{
	return (long)0;
}

// FUNCTION: SADX 0x004bb9a0
void CameraSetCameraMi(struct _OBJ_CAMERAENTRY *pCameraEntry)
{
	if (DAT_05b42940 == 0)
	{
		return;
	}
	*(short *)((char *)pCameraSystemWork + 4) = DAT_05b4294a;
	*(char *)((char *)pCameraSystemWork + 0xb) = DAT_05b4294c;
	*(char *)((char *)pCameraSystemWork + 6) = DAT_05b4294d;
	*(int *)((char *)pCameraSystemWork + 0xc) = DAT_05b42950;
	*(char *)((char *)pCameraSystemWork + 8) = DAT_05b42948;
	*(char *)((char *)pCameraSystemWork + 9) = DAT_05b42954;
	*(int *)((char *)pCameraSystemWork + 0x10) = DAT_05b42958;
	*(char *)((char *)pCameraSystemWork + 7) = *(char *)((char *)DAT_05b4299c[0] + (*(char *)((char *)pCameraSystemWork + 6)) * 16 + 5);
	*(int *)pCameraSystemWork = 1;
	*(int *)((char *)pCameraSystemWork + 0x14) = 0;
	*(int *)((char *)pObjAdjustParam + 0x14) = 0;
	DAT_05b42940 = 0;
}

// FUNCTION: SADX 0x004bbcf0
void CameraReleaseCollisionCamera()
{
	if (*(signed char *)((char *)pCameraSystemWork + 6) == 0x40 || *(signed char *)((char *)pCameraSystemWork + 6) == 0x4c)
	{
		FUN_004bee10();
		SetAdjustMode(5);
	}
}

// STUB: SADX 0x004bbd30
void FUN_004bbd30(short param_1, struct _OBJ_CAMERAENTRY *param_2)
{
}

// STUB: SADX 0x004bbdd0
void CameraManagerRegional(short ssCameraEntry, struct _OBJ_CAMERAENTRY *pCameraEntry)
{
}

// STUB: SADX 0x004bbf90
void CameraManagerEvent(short ssCameraEntry, struct _OBJ_CAMERAENTRY *pCameraEntry)
{
}

// FUNCTION: SADX 0x004bc160
void InitFreeCamera()
{
	DAT_05b42a74 |= 0x8000000c;
	DAT_05b42860 = 0x3c;
}

// FUNCTION: SADX 0x004bc180
void ResetFreeCamera()
{
	DAT_05b42a74 = DAT_05b42a74 | 0x80000008;
	DAT_05b42860 = 0x3c;
}

// FUNCTION: SADX 0x004bc1a0
void SetFreeCameraMode(long sw)
{
	if (sw != 0)
	{
		if ((DAT_05b42a74 & 4) == 0)
		{
			DAT_05b42a74 |= 4;
			DAT_05b42a74 |= 0x80000000;
		}
	}
	else
	{
		DAT_05b42a74 &= 0xfffffffb;
		DAT_05b42a74 |= 0x80000000;
	}
}

// FUNCTION: SADX 0x004bc200
void SetFreeCamera(long sw)
{
	if (sw != 0)
	{
		if ((DAT_05b42a74 & 1) == 0)
		{
			DAT_05b42a74 = DAT_05b42a74 | 1;
			DAT_05b42a74 = DAT_05b42a74 | 0x80000000;
		}
	}
	else
	{
		DAT_05b42a74 = DAT_05b42a74 & 0xfffffffe;
		DAT_05b42a74 = DAT_05b42a74 | 0x80000000;
	}
}

// FUNCTION: SADX 0x004bc260
long GetFreeCamera()
{
	return (DAT_05b42a74 & 1) != 0;
}

// FUNCTION: SADX 0x004bd3d0
void setdistdata()
{
	int local_ci;
	int local_10;
	int local_8g;
	local_8g = ((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744;
	local_ci = (unsigned char)(local_8g >> 8);
	local_10 = (unsigned char)local_8g;
	switch (local_ci)
	{
	case 0xc:
		if (GetPlayerCharacterName(0) == 5)
		{
			DAT_05b42828 = 15.0;
			DAT_05b4282c = 30.0;
		}
		else
		{
			DAT_05b42828 = 15.0;
			DAT_05b4282c = 50.0;
		}
		break;
	case 0x21:
		if (local_10 == 2)
		{
			DAT_05b42828 = 16.0;
			DAT_05b4282c = 50.0;
		}
		else
		{
			DAT_05b42828 = 16.0;
			DAT_05b4282c = 70.0;
		}
		break;
	default:
		DAT_05b42828 = 16.0;
		DAT_05b4282c = 70.0;
		break;
	}
}

// STUB: SADX 0x004bd4b0
void calcfreecamerapos()
{
}

// FUNCTION: SADX 0x004bd800
long CameraCollisionCube(struct _OBJ_CAMERAENTRY *pCameraEntry)
{
	float fVar4;
	float fVar1;
	float fVar2;
	float fVar3;
	fVar1 = DAT_05baf368[0]->pos.x - *(float *)((char *)pCameraEntry + 8);
	fVar4 = DAT_05baf368[0]->pos.y - *(float *)((char *)pCameraEntry + 0xc) + 4.0;
	fVar2 = DAT_05baf368[0]->pos.z - *(float *)((char *)pCameraEntry + 0x10);
	fVar3 = fVar1 * fVar1 + fVar4 * fVar4 + fVar2 * fVar2;
	if (fVar3 < *(float *)((char *)pCameraEntry + 0x1c))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x004bddd0
void FUN_004bddd0()
{
}

// FUNCTION: SADX 0x004bde80
void CamcontSetCameraCAMSTATUS(struct taskwk *pTaskWork)
{
	pTaskWork->pos.x = *(float *)((char *)camcont_wp + 0xc);
	pTaskWork->pos.y = *(float *)((char *)camcont_wp + 0x10);
	pTaskWork->pos.z = *(float *)((char *)camcont_wp + 0x14);
	pTaskWork->ang.x = *(long *)((char *)camcont_wp + 0x24);
	pTaskWork->ang.y = *(long *)((char *)camcont_wp + 0x28);
	pTaskWork->ang.z = *(long *)((char *)camcont_wp + 0x2c);
}

// STUB: SADX 0x004bdee0
void CamcontSetCameraLOOKAT(struct taskwk *pTaskWork)
{
}

// FUNCTION: SADX 0x004bdfe0
void CamcontSetCameraTGTOFST(struct taskwk *pTaskWork)
{
	float fVar1;
	fVar1 = njCos(*(long *)((char *)camcont_wp + 0x24)) * *(float *)((char *)camcont_wp + 8);
	*(float *)((char *)pTaskWork + 0x24) = *(float *)((char *)camcont_wp + 0x1c) - njSin(*(long *)((char *)camcont_wp + 0x24)) * *(float *)((char *)camcont_wp + 8);
	*(float *)((char *)pTaskWork + 0x20) = njSin(*(long *)((char *)camcont_wp + 0x28)) * fVar1 + *(float *)((char *)camcont_wp + 0x18);
	*(float *)((char *)pTaskWork + 0x28) = njCos(*(long *)((char *)camcont_wp + 0x28)) * fVar1 + *(float *)((char *)camcont_wp + 0x20);
	pTaskWork->ang.x = *(long *)((char *)camcont_wp + 0x24);
	pTaskWork->ang.y = *(long *)((char *)camcont_wp + 0x28);
	pTaskWork->ang.z = *(long *)((char *)camcont_wp + 0x2c);
}

// FUNCTION: SADX 0x004be0b0
void AddCameraOffset(struct NJS_POINT3 *vecOffset)
{
	*(float *)((char *)pCameraSystemWork + 0x98) += vecOffset->x;
	*(float *)((char *)pCameraSystemWork + 0x9c) += vecOffset->y;
	*(float *)((char *)pCameraSystemWork + 0xa0) += vecOffset->z;
}

// FUNCTION: SADX 0x004be350
void CameraCancelCamera()
{
	int local_10;
	int local_cj;
	char local_5i;
	local_5i = *(char *)((char *)pCameraSystemWork + 8);
	local_10 = *(char *)((char *)DAT_05b42974 + 1 + *(short *)((char *)pCameraSystemWork + 4) * 64);
	local_cj = *(char *)((char *)DAT_05b42974 + 1 + *(short *)((char *)pCameraSystemWork + local_5i * 2 + 0x30) * 64);
	*(short *)((char *)pCameraSystemWork + 4) = *(short *)((char *)pCameraSystemWork + local_5i * 2 + 0x30);
	*(char *)((char *)pCameraSystemWork + 0xb) = *(char *)((char *)pCameraSystemWork + local_5i + 0x3c);
	*(char *)((char *)pCameraSystemWork + 6) = *(char *)((char *)pCameraSystemWork + local_5i + 0x78);
	*(int *)((char *)pCameraSystemWork + 0xc) = *(int *)((char *)pCameraSystemWork + local_5i * 4 + 0x44);
	*(char *)((char *)pCameraSystemWork + 8) = *(char *)((char *)pCameraSystemWork + local_5i * 4 + 0x18);
	if (0xa <= local_10 && local_cj >= 0xa)
	{
		*(char *)((char *)pCameraSystemWork + 9) = 0;
	}
	else
	{
		*(char *)((char *)pCameraSystemWork + 9) = *(char *)((char *)pCameraSystemWork + local_5i + 0x7e);
	}
	if (local_10 < local_cj)
	{
		DAT_05b42990 = 1;
	}
	if (0xa <= local_10 && local_cj >= 0xa)
	{
		*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)DAT_05b4298c + 4);
	}
	else
	{
		*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)pCameraSystemWork + local_5i * 4 + 0x5c);
	}
	*(char *)((char *)pCameraSystemWork + 7) = *(char *)((char *)DAT_05b4299c[0] + (*(char *)((char *)pCameraSystemWork + 6)) * 16 + 5);
	*(int *)pCameraSystemWork = 1;
	*(int *)((char *)pCameraSystemWork + 0x14) = 0;
	*(int *)((char *)pObjAdjustParam + 0x14) = 0;
}

// FUNCTION: SADX 0x004be4d0
void CameraSetNormalCamera(short ssCameraMode, unsigned char ucAdjustType)
{
	if (*(char *)((char *)pCameraSystemWork + 8) == 0)
	{
		*(int *)((char *)pCameraSystemWork + 0x18) = *(char *)((char *)pCameraSystemWork + 8);
		*(short *)((char *)pCameraSystemWork + 0x30) = *(short *)((char *)pCameraSystemWork + 4);
		*(char *)((char *)pCameraSystemWork + 0x3c) = *(char *)((char *)pCameraSystemWork + 0xb);
		*(char *)((char *)pCameraSystemWork + 0x78) = *(char *)((char *)pCameraSystemWork + 6);
		*(int *)((char *)pCameraSystemWork + 0x44) = *(int *)((char *)pCameraSystemWork + 0xc);
		if (*(short *)((char *)pCameraSystemWork + 4) != -1)
		{
			*(char *)((char *)pCameraSystemWork + 0x7e) = *(char *)((char *)DAT_05b42974 + *(short *)((char *)pCameraSystemWork + 4) * 64 + 2);
		}
		else
		{
			*(char *)((char *)pCameraSystemWork + 0x7e) = 0x15;
		}
		*(int *)((char *)pCameraSystemWork + 0x5c) = *(int *)((char *)DAT_05b4298c + *(char *)((char *)pCameraSystemWork + 0x7e) * 8 + 4);
		*(short *)((char *)pCameraSystemWork + 4) = -1;
		*(char *)((char *)pCameraSystemWork + 8) = 0;
		*(char *)((char *)pCameraSystemWork + 6) = ssCameraMode;
		*(int *)((char *)pCameraSystemWork + 0xc) = *(int *)((char *)DAT_05b4299c[0] + ssCameraMode * 16);
		*(char *)((char *)pCameraSystemWork + 9) = ucAdjustType;
		*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)DAT_05b4298c + ucAdjustType * 8 + 4);
		*(int *)((char *)pObjAdjustParam + 0x14) = 0;
		if (*(int *)((char *)DAT_05b4298c + *(char *)((char *)pCameraSystemWork + 9) * 8) != 0)
		{
			*(char *)((char *)pCameraSystemWork + 0xb) = *(char *)((char *)pCameraSystemWork + 0xb) | 1;
		}
		*(char *)((char *)pCameraSystemWork + 7) = *(char *)((char *)DAT_05b4299c[0] + *(char *)((char *)pCameraSystemWork + 6) * 16 + 5);
		*(int *)pCameraSystemWork = 1;
	}
}

// STUB: SADX 0x004be650
void CameraSetEventCamera(short ssCameraMode, unsigned char ucAdjustType)
{
}

// FUNCTION: SADX 0x004be800
void CameraSetEventCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect)
{
	CameraReleaseCollisionCamera();
	if ((signed char)*(char *)((char *)pCameraSystemWork + 8) <= 2)
	{
		if (*(char *)((char *)pCameraSystemWork + 8) != 2)
		{
			*(int *)((char *)pCameraSystemWork + 0x20) = *(char *)((char *)pCameraSystemWork + 8);
			*(short *)((char *)pCameraSystemWork + 0x34) = *(short *)((char *)pCameraSystemWork + 4);
			*(char *)((char *)pCameraSystemWork + 0x3e) = *(char *)((char *)pCameraSystemWork + 0xb);
			*(char *)((char *)pCameraSystemWork + 0x7a) = *(char *)((char *)pCameraSystemWork + 6);
			*(int *)((char *)pCameraSystemWork + 0x4c) = *(int *)((char *)pCameraSystemWork + 0xc);
			if (*(short *)((char *)pCameraSystemWork + 4) != -1)
			{
				*(char *)((char *)pCameraSystemWork + 0x80) = *(char *)(DAT_05b42974 + *(short *)((char *)pCameraSystemWork + 4) * 64 + 2);
			}
			else
			{
				*(char *)((char *)pCameraSystemWork + 0x80) = 0x15;
			}
			*(int *)((char *)pCameraSystemWork + 0x64) = *(int *)((char *)DAT_05b4298c + *(char *)((char *)pCameraSystemWork + 0x80) * 8 + 4);
			*(char *)((char *)pCameraSystemWork + 8) = 2;
		}
		*(short *)((char *)pCameraSystemWork + 4) = -1;
		*(char *)((char *)pCameraSystemWork + 6) = 0xff;
		*(int *)((char *)pCameraSystemWork + 0xc) = (int)fnCamera;
		*(char *)((char *)pCameraSystemWork + 9) = ucAdjustType;
		*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)DAT_05b4298c + *(char *)((char *)pCameraSystemWork + 9) * 8 + 4);
		*(int *)((char *)pObjAdjustParam + 0x14) = 0;
		*(char *)((char *)pCameraSystemWork + 0xb) = 2;
		if (*(int *)((char *)DAT_05b4298c + *(char *)((char *)pCameraSystemWork + 9) * 8) != 0)
		{
			*(char *)((char *)pCameraSystemWork + 0xb) = *(char *)((char *)pCameraSystemWork + 0xb) | 1;
		}
		*(char *)((char *)pCameraSystemWork + 7) = scCameraDirect;
		*(int *)pCameraSystemWork = 1;
	}
}

// FUNCTION: SADX 0x004be9a0
void CameraReleaseEventCamera()
{
	if (*(char *)((char *)pCameraSystemWork + 8) == 2)
	{
		*(short *)((char *)pCameraSystemWork + 4) = *(short *)((char *)pCameraSystemWork + 0x34);
		*(char *)((char *)pCameraSystemWork + 0xb) = *(char *)((char *)pCameraSystemWork + 0x3e);
		*(char *)((char *)pCameraSystemWork + 6) = *(char *)((char *)pCameraSystemWork + 0x7a);
		*(int *)((char *)pCameraSystemWork + 0xc) = *(int *)((char *)pCameraSystemWork + 0x4c);
		*(char *)((char *)pCameraSystemWork + 9) = *(char *)((char *)pCameraSystemWork + 0x80);
		*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)pCameraSystemWork + 0x64);
		*(char *)((char *)pCameraSystemWork + 8) = *(char *)((char *)pCameraSystemWork + 0x20);
		*(char *)((char *)pCameraSystemWork + 7) = *(char *)((char *)DAT_05b4299c[0] + (*(char *)((char *)pCameraSystemWork + 6)) * 16 + 5);
		*(int *)pCameraSystemWork = 1;
		*(int *)((char *)pCameraSystemWork + 0x14) = 0;
		*(int *)((char *)pObjAdjustParam + 0x14) = 0;
		if (*(char *)((char *)pCameraSystemWork + 8) == 0 && DAT_05b42a78 != -1)
		{
			CameraSetNormalCamera((short)DAT_05b42a78, DAT_05b42994);
		}
	}
	DAT_05b428e8 = 0;
}

// FUNCTION: SADX 0x004beac0
void CameraSetCollisionCameraFunc(void (*fnCamera)(struct _OBJ_CAMERAPARAM *), unsigned char ucAdjustType, signed char scCameraDirect)
{
	if ((signed char) *(char *)((char *)pCameraSystemWork + 8) <= 4)
	{
		if ((signed char) *(char *)((char *)pCameraSystemWork + 8) != 4)
		{
			*(int *)((char *)pCameraSystemWork + 0x28) = (signed char) *(char *)((char *)pCameraSystemWork + 8);
			*(short *)((char *)pCameraSystemWork + 0x38) = *(short *)((char *)pCameraSystemWork + 4);
			*(char *)((char *)pCameraSystemWork + 0x40) = *(char *)((char *)pCameraSystemWork + 0xb);
			*(char *)((char *)pCameraSystemWork + 0x7c) = *(char *)((char *)pCameraSystemWork + 6);
			*(int *)((char *)pCameraSystemWork + 0x54) = *(int *)((char *)pCameraSystemWork + 0xc);
			if ((short) *(short *)((char *)pCameraSystemWork + 4) != -1)
			{
				*(char *)((char *)pCameraSystemWork + 0x82) = *(char *)((char *)DAT_05b42974 + (short) *(short *)((char *)pCameraSystemWork + 4) * 64 + 2);
			}
			else
			{
				*(char *)((char *)pCameraSystemWork + 0x82) = 0x15;
			}
			*(int *)((char *)pCameraSystemWork + 0x6c) = *(int *)((char *)DAT_05b4298c + (signed char) *(char *)((char *)pCameraSystemWork + 0x82) * 8 + 4);
			*(char *)((char *)pCameraSystemWork + 8) = 4;
		}
		*(short *)((char *)pCameraSystemWork + 4) = -1;
		*(char *)((char *)pCameraSystemWork + 6) = 0xff;
		*(int *)((char *)pCameraSystemWork + 0xc) = (int) fnCamera;
		*(char *)((char *)pCameraSystemWork + 9) = ucAdjustType;
		*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)DAT_05b4298c + (signed char) *(char *)((char *)pCameraSystemWork + 9) * 8 + 4);
		*(int *)((char *)pObjAdjustParam + 0x14) = 0;
		*(char *)((char *)pCameraSystemWork + 0xb) = 2;
		if (*(int *)((char *)DAT_05b4298c + (signed char) *(char *)((char *)pCameraSystemWork + 9) * 8) != 0)
		{
			*(char *)((char *)pCameraSystemWork + 0xb) = (signed char) *(char *)((char *)pCameraSystemWork + 0xb) | 1;
		}
		*(char *)((char *)pCameraSystemWork + 7) = scCameraDirect;
		*(int *)pCameraSystemWork = 1;
	}
}

// STUB: SADX 0x004bec60
void FUN_004bec60(short ucAdjustType, unsigned char ucCameraDirect)
{
}

// FUNCTION: SADX 0x004bee10
void FUN_004bee10(void)
{
	if (*(char *)((char *)pCameraSystemWork + 8) == 4)
	{
		*(short *)((char *)pCameraSystemWork + 4) = *(short *)((char *)pCameraSystemWork + 0x38);
		*(char *)((char *)pCameraSystemWork + 0xb) = *(char *)((char *)pCameraSystemWork + 0x40);
		*(char *)((char *)pCameraSystemWork + 6) = *(char *)((char *)pCameraSystemWork + 0x7c);
		*(int *)((char *)pCameraSystemWork + 0xc) = *(int *)((char *)pCameraSystemWork + 0x54);
		*(char *)((char *)pCameraSystemWork + 9) = *(char *)((char *)pCameraSystemWork + 0x82);
		*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)pCameraSystemWork + 0x6c);
		*(char *)((char *)pCameraSystemWork + 8) = *(char *)((char *)pCameraSystemWork + 0x28);
		*(char *)((char *)pCameraSystemWork + 7) = *(char *)((char *)DAT_05b4299c[0] + (*(char *)((char *)pCameraSystemWork + 6)) * 16 + 5);
		*(int *)pCameraSystemWork = 1;
		*(int *)((char *)pCameraSystemWork + 0x14) = 0;
		*(int *)((char *)pObjAdjustParam + 0x14) = 0;
		if (*(char *)((char *)pCameraSystemWork + 8) == 0 && DAT_05b42a78 != -1)
		{
			CameraSetNormalCamera((short)DAT_05b42a78, (unsigned char)DAT_05b42994);
		}
	}
}

// FUNCTION: SADX 0x004bef20
void FUN_004bef20(struct _CameraSystemWork *param_1)
{
	DAT_05b429a8 = *(float *)((char *)param_1 + 0x30);
	DAT_05b429ac = *(float *)((char *)param_1 + 0x34);
	DAT_05b429b0 = *(float *)((char *)param_1 + 0x38);
	DAT_05b429b4 = *(float *)((char *)param_1 + 0x24);
	DAT_05b429b8 = *(float *)((char *)param_1 + 0x28);
	DAT_05b429bc = *(float *)((char *)param_1 + 0x2c);
	DAT_05b429a4 = *(short *)((char *)param_1 + 0x20);
	DAT_05b429a6 = *(short *)((char *)param_1 + 0x22);
	DAT_05b429c0 = *(float *)((char *)param_1 + 0x3c);
	DAT_05b429c4 = *(int *)((char *)pCameraSystemWork + 0x14);
}

// FUNCTION: SADX 0x004befb0
long IsEventCamera()
{
	if (*(char *)((char *)pCameraSystemWork + 8) == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x004befd0
long IsCompulsionCamera()
{
	if (*(char *)((char *)pCameraSystemWork + 8) == 3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x004beff0
unsigned long GetCameraTimer()
{
	return DAT_05b429a0;
}

// FUNCTION: SADX 0x004bf000
void ResetCameraTimer()
{
	DAT_05b429a0 = 0;
}

// FUNCTION: SADX 0x004bf010
void SetAdjustMode(long AdjustType)
{
	*(char *)((char *)pCameraSystemWork + 9) = (char)AdjustType;
	*(int *)((char *)pCameraSystemWork + 0x10) = *(int *)((char *)DAT_05b4298c + *(char *)((char *)pCameraSystemWork + 9) * 8 + 4);
	*(int *)((char *)pObjAdjustParam + 0x14) = 0;
}

// FUNCTION: SADX 0x004bf050
long GetAdjustMode()
{
	return *(char *)((char *)pCameraSystemWork + 9);
}

// FUNCTION: SADX 0x004bf060
long GetCameraMode()
{
	return *(char *)((char *)pCameraSystemWork + 6);
}

// FUNCTION: SADX 0x004bf070
void FUN_004bf070(int param_1)
{
	*(short *)((char *)pCameraSystemWork + 4) = 0xffff;
	*(char *)((char *)pCameraSystemWork + 6) = (char)param_1;
	*(int *)((char *)pCameraSystemWork + 0xc) = *(int *)((char *)*(int *)DAT_05b4299c + (param_1 << 4));
}

// FUNCTION: SADX 0x004bf0b0
void FUN_004bf0b0(struct _CameraSystemWork *param_1, struct _CameraSystemWork *param_2)
{
	float local_10m;
	float local_14;
	float local_8g;
	float local_cj;

	local_10m = *(float *)((char *)param_1 + 0x20) - *(float *)((char *)param_2 + 0x20);
	local_14 = *(float *)((char *)param_1 + 0x24) - *(float *)((char *)param_2 + 0x24);
	local_8g = *(float *)((char *)param_1 + 0x28) - *(float *)((char *)param_2 + 0x28);
	local_cj = local_10m * local_10m + local_14 * local_14 + local_8g * local_8g;
	if (0.010000000707805157 > local_cj)
	{
		if (DiffAngle(*(int *)((char *)param_1 + 0x14), *(int *)((char *)param_2 + 0x14)) < 0x5b)
		{
			if (DiffAngle(*(int *)((char *)param_1 + 0x18), *(int *)((char *)param_2 + 0x18)) < 0x5b)
			{
				if (DiffAngle(*(int *)((char *)param_1 + 0x1c), *(int *)((char *)param_2 + 0x1c)) < 0x5b)
				{
					switch (*(char *)((char *)pCameraSystemWork + 9))
					{
						case 1:
							SetAdjustMode(3);
							break;
						case 0:
						case 2:
						case 3:
						case 4:
							SetAdjustMode(0);
							break;
					}
				}
			}
		}
	}
}

// STUB: SADX 0x004bf1b0
void FUN_004bf1b0(void)
{
}

// STUB: SADX 0x004bf1e0
void FUN_004bf1e0(void)
{
}

// FUNCTION: SADX 0x004bf260
void FUN_004bf260(void)
{
	DAT_05b4295c = DAT_05b42a7c->pos;
}

// FUNCTION: SADX 0x004bf290
void FUN_004bf290()
{
	DAT_05b4289c = DAT_05b42a7c->pos.x - DAT_05b4295c.x;
	DAT_05b428a0 = DAT_05b42a7c->pos.y - DAT_05b4295c.y;
	DAT_05b428a4 = DAT_05b42a7c->pos.z - DAT_05b4295c.z;
	DAT_05b4295c = DAT_05b42a7c->pos;
}

// FUNCTION: SADX 0x004bf300
long CheckAdjustCollisionMode()
{
	switch (GetAdjustMode())
	{
		case 5:
		case 7:
		case 9:
		case 0xb:
		case 0xd:
		case 0xf:
		case 0x11:
		case 0x13:
		case 0x15:
		case 0x17:
		case 0x19:
		case 0x1a:
			return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004bf360
void FUN_004bf360(char param_1)
{
	((char *)pCameraSystemWork)[7] = param_1;
}

// FUNCTION: SADX 0x004bf370
long CameraCameraAction(struct NJS_CACTION *caction, float frame)
{
	switch (DAT_05b4259c)
	{
		case 0:
			CameraSetEventCameraFunc((void (__cdecl *)(_OBJ_CAMERAPARAM *))FUN_005b5aa0, 0, 0);
		case 2:
			DAT_05b4259c = 1;
			DAT_05b425cc = caction;
			DAT_05b4293c = frame;
			return 0;
		default:
			return 1;
	}
}

// STUB: SADX 0x004bf590
long addcolCube(struct _OBJ_CAMERAENTRY *entry, struct NJS_POINT3 *pos)
{
	return (long)0;
}

// FUNCTION: SADX 0x004bf650
long FUN_004bf650(float *param_1, float *param_2)
{
	float fVar4;
	float fVar1;
	float fVar2;
	float fVar3;
	fVar1 = *param_2 - *(float *)((char *)param_1 + 8);
	fVar4 = param_2[1] - *(float *)((char *)param_1 + 0xc);
	fVar2 = param_2[2] - *(float *)((char *)param_1 + 0x10);
	fVar3 = fVar1 * fVar1 + fVar4 * fVar4 + fVar2 * fVar2;
	if (fVar3 < *(float *)((char *)param_1 + 0x1c))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x004bfcb0
void CameraPositionSmooth(struct NJS_POINT3 *last, struct NJS_POINT3 *pos)
{
	if (DAT_05b42a88 != 0)
	{
		pos->x = (pos->x - last->x) * (float)(0x1e - DAT_05b42a88) * DAT_0095cbf8 + last->x;
		pos->y = (pos->y - last->y) * (float)(0x1e - DAT_05b42a88) * DAT_0095cbf8 + last->y;
		pos->z = (pos->z - last->z) * (float)(0x1e - DAT_05b42a88) * DAT_0095cbf8 + last->z;
		DAT_05b42a88 = DAT_05b42a88 - 1;
	}
}

// FUNCTION: SADX 0x004bfd60
long MSetPositionNW(struct NJS_POINT3 *p, struct NJS_POINT3 *v, struct Angle3 *a, float r)
{
	return MSetPositionIgnoreAttribute(p, v, a, 0x400002, r);
}

// FUNCTION: SADX 0x004bfd90
void cameraDisplay(struct task *tp)
{
	CameraFilter();
}

// FUNCTION: SADX 0x004c0320
void FUN_004c0320()
{
	int local_8;
	for (local_8 = 0; local_8 < 0x32; local_8++)
	{
		DAT_05b425d0[local_8] = DAT_05baf368[0]->pos;
	}
	DAT_05b425c8 = 0;
}

// STUB: SADX 0x004c0380
void setChaseRingBuffer()
{
}

// FUNCTION: SADX 0x004c04b0
struct NJS_POINT3 *FollowRingData(long num)
{
	int local_8;
	local_8 = DAT_05b425c8 - num;
	if (local_8 < 0)
	{
		local_8 += 0x32;
	}
	return &DAT_05b425d0[local_8];
}
