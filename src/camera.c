#include "decls.h"
extern int DAT_05b425c8;
extern NJS_POINT3 DAT_05b425d0[0x32];
extern float DAT_05b4289c;
extern float DAT_05b428a0;
extern float DAT_05b428a4;
extern struct NJS_POINT3 DAT_05b4295c;
extern short *DAT_05baf368;
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
	int local_8;

	local_8 = *(char *)((char *)pCameraSystemWork + 0x6);
	if (local_8 < 0x1c || local_8 > 0x1e)
	{
		DAT_05b42968 = new_view_angle;
	}
	else
	{
		if (GetAdjustMode())
		{
			DAT_05b42968 = AdjustAngle(DAT_05b42968, 0x31c7, 0x12);
		}
		else
		{
			DAT_05b42968 = 0x31c7;
		}
	}
	___njSetPerspective(DAT_05b42968);
	DAT_05b42a80 = DAT_05b42968;
}

// FUNCTION: SADX 0x004bafb0
void FUN_004bafb0(void)
{
	DAT_05b42968 = 0x31c7;
	___njSetPerspective(DAT_05b42968);
	DAT_05b42a80 = DAT_05b42968;
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

// FUNCTION: SADX 0x004bbcf0
void CameraReleaseCollisionCamera()
{
	if (*(signed char *)((char *)pCameraSystemWork + 6) == 0x40 || *(signed char *)((char *)pCameraSystemWork + 6) == 0x4c)
	{
		FUN_004bee10();
		SetAdjustMode(5);
	}
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

// STUB: SADX 0x004bd800
long CameraCollisionCube(struct _OBJ_CAMERAENTRY *pCameraEntry)
{
	return (long)0;
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

// FUNCTION: SADX 0x004be0b0
void AddCameraOffset(struct NJS_POINT3 *vecOffset)
{
	*(float *)((char *)pCameraSystemWork + 0x98) += vecOffset->x;
	*(float *)((char *)pCameraSystemWork + 0x9c) += vecOffset->y;
	*(float *)((char *)pCameraSystemWork + 0xa0) += vecOffset->z;
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

// STUB: SADX 0x004bf300
long CheckAdjustCollisionMode()
{
	return (long)0;
}

// FUNCTION: SADX 0x004bf360
void FUN_004bf360(char param_1)
{
	((char *)pCameraSystemWork)[7] = param_1;
}

// STUB: SADX 0x004bf370
long CameraCameraAction(struct NJS_CACTION *caction, float frame)
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
		DAT_05b425d0[local_8] = *(NJS_POINT3 *)((char *)DAT_05baf368 + 0x20);
	}
	DAT_05b425c8 = 0;
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
