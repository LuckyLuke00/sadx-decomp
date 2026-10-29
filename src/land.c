#include "decls.h"
extern long boolLandCollision;
extern unsigned char DAT_05b3e065;
extern unsigned char DAT_05cb5630[256];
extern void FUN_004fdaf0();
extern void FUN_004feb40();
extern void FUN_004fdae0(struct task *param_1);
extern void FUN_004feb30(struct task *param_1);
extern void LandLoad(long stage, long act);
void FUN_004fdaf0();
void FUN_004feb40();
void FUN_004fdae0(struct task *param_1);
void FUN_004feb30(struct task *param_1);
void LandLoad(long stage, long act);
float FUN_004fd8e0(float *param_1, float *param_2);
extern int DAT_05b9d838;
extern int DAT_05b42a84;
extern int DAT_05b3e0d0;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern float DAT_05b3ebc8;
extern float DAT_05b3ebcc;
extern float DAT_05b3ebd0;
extern int DAT_05b3ebdc;
extern int DAT_05b3ebc4;
extern struct obj DAT_05cbbb50[256];
extern int objLandTable[8][8];
extern short DAT_05cba940;
extern char DAT_05cbef5c;
extern char DAT_05cbef5d;
extern int DAT_05cb7938;
extern int DAT_05cbaf4c;
extern int DAT_05cb793c;
extern float DAT_05cba944;
extern short DAT_05cb5730;
extern short DAT_05cbaf48;
extern int DAT_05cbef54;
extern int DAT_05cbef58;

// FUNCTION: SADX 0x004fcd50
void SetLandform(struct task *pTask)
{
	struct taskwk *local_8g;

	local_8g = pTask->twp;
	switch (local_8g->mode)
	{
		case 0:
			InitializeLandWork(pTask);
			DAT_05cbaf4c = (int)local_8g;
			FUN_004fed30();
			pTask->disp = ManageGroundDisplayer;
			pTask->dest = EndGround;
			SetMleriRangeRad(400.0f);
			DAT_05b3e065 = 0;
		case 2:
			InitializeGround();
			local_8g->mode = 1;
		case 1:
			ManageGround(pTask);
			break;
		default:
			local_8g->mode = 0;
			break;
	}
}

// FUNCTION: SADX 0x004fcdf0
void InitializeLandWork(struct task *pTask)
{
	DAT_05cba940 = 0;
	DAT_05cbef5c = 0;
	DAT_05cbef5d = 0;
	DAT_05cb7938 = 0;
	DAT_05cbaf4c = 0;
	DAT_05cb793c = 0;
	DAT_05cba944 = 0.0f;
	boolLandDisplay = 1;
	boolLandCollision = 1;
	DAT_05cb5730 = 0;
	DAT_05cbaf48 = 0;
	DAT_05cbef54 = 0;
	DAT_05cbef58 = 0;
}

// STUB: SADX 0x004fce70
void LandLoad(long stage, long act)
{
}

#pragma optimize("", off)
// STUB: SADX 0x004fd020
void LandRelease(long stage, long act)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004fd1e0
void LandChangeStage(short ssGap)
{
	if (ChkGameMode() == 0)
		return;
	LandRelease((long)DAT_05cbef5c, (long)DAT_05cbef5d);
	if (DAT_05cbaf4c != 0)
	{
		*(char *)DAT_05cbaf4c = 2;
	}
	DAT_05cbef5d += ssGap;
}

// FUNCTION: SADX 0x004fd230
void LandClearLandTable(long stage, long act)
{
	objLandTable[stage][act] = 0;
}

// FUNCTION: SADX 0x004fd250
void LandChangeLandTable(struct _OBJ_LANDTABLE *pOLT)
{
	objLandTable[(int)DAT_05cbef5c][(int)DAT_05cbef5d] = (int)pOLT;
	*(char *)DAT_05cbaf4c = 2;
	DAT_05cbef54 = 0;
	DAT_05cbef58 = 0;
}

// STUB: SADX 0x004fd290
void InitializeGround()
{
}

// FUNCTION: SADX 0x004fd360
void EndGround(struct task *pTask)
{
	LandRelease((long)DAT_05cbef5c, (long)DAT_05cbef5d);
	InitializeLandWork(pTask);
}

// FUNCTION: SADX 0x004fd390
void ManageGround(struct task *pTask)
{
	struct taskwk *local_8;
	local_8 = pTask->twp;
	ResetMaterial();
	SaveConstantAttr();
	if (boolLandDisplay == 1 && DAT_05b9d838 == 0)
	{
		if (DAT_05b42a84 != 0)
		{
			ListGroundForDrawing();
			npSetZCompareMode(3);
			npSetZCompare();
			DrawGround();
			if (DAT_05b3e0d0 < 1)
			{
				MotionGround();
			}
			if (DAT_05b3e0d0 < 2 || ((DAT_05b9d724 << 8) | DAT_05b9d744) == 0x2103)
			{
				DrawMotionGround();
			}
			npSetZCompareMode(1);
			npSetZCompare();
		}
		else
		{
			if (DAT_05b3e0d0 < 1)
			{
				MotionGround();
			}
		}
	}
	LoadConstantAttr();
	ResetMaterial();
}

// FUNCTION: SADX 0x004fd450
void ManageGroundDisplayer(struct task *pTask)
{
	struct taskwk *local_8;
	local_8 = pTask->twp;
	ResetMaterial();
	SaveConstantAttr();
	if (boolLandDisplay == 1 && DAT_05b9d838 == 0)
	{
		npSetZCompareMode(3);
		npSetZCompare();
		ListGroundForDrawing();
		DrawGround();
		if (DAT_05b3e0d0 < 2 || ((DAT_05b9d724 << 8) | DAT_05b9d744) == 0x2103)
		{
			DrawMotionGround();
		}
		npSetZCompareMode(1);
		npSetZCompare();
	}
	LoadConstantAttr();
	ResetMaterial();
}

#pragma optimize("", off)
// STUB: SADX 0x004fd4e0
void DrawGround()
{
}
#pragma optimize("", on)

// STUB: SADX 0x004fd700
void land_DrawObject(struct obj *obj, struct _OBJ_LANDENTRY *landEnt)
{
}

// FUNCTION: SADX 0x004fd8e0
float FUN_004fd8e0(float *param_1, float *param_2)
{
	float fVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	fVar4 = *param_2 - *param_1;
	fVar2 = param_2[1] - param_1[1];
	fVar3 = param_2[2] - param_1[2];
	fVar1 = fVar4 * fVar4 + fVar2 * fVar2 + fVar3 * fVar3;
	return fVar1;
}

#pragma optimize("", off)
// STUB: SADX 0x004fd940
void DrawMotionGround()
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x004fda40
void MotionGround()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004fdae0
void FUN_004fdae0(struct task *param_1)
{
	boolLandDisplay = 0;
}

// FUNCTION: SADX 0x004fdaf0
void FUN_004fdaf0()
{
	boolLandDisplay = 1;
}

// FUNCTION: SADX 0x004feb30
void FUN_004feb30(struct task *param_1)
{
	boolLandCollision = 0;
}

// FUNCTION: SADX 0x004feb40
void FUN_004feb40()
{
	boolLandCollision = 1;
}

// STUB: SADX 0x004feb50
void RegisterCollisionEntry(long slAttribute, struct task *pTask, struct obj *pObject)
{
}

// STUB: SADX 0x004fec40
void WithdrawCollisionEntry(struct task *pTask, struct obj *pObject)
{
}

// FUNCTION: SADX 0x004fed30
void FUN_004fed30()
{
	short sVar1;

	for (sVar1 = 0xff; sVar1 >= 0; sVar1--)
	{
		DAT_05cb5630[sVar1] = 0;
	}
}

// STUB: SADX 0x004fed70
struct obj *GetMobileLandObject()
{
	return (struct obj *)0;
}

// FUNCTION: SADX 0x004fee10
void ReleaseMobileLandObject(struct obj *pObjLandObject)
{
	short local_8;
	for (local_8 = 0xff; local_8 >= 0; local_8--)
	{
		if (pObjLandObject == &DAT_05cbbb50[local_8])
			break;
	}
	if (local_8 >= 0)
	{
		DAT_05cb5630[local_8] = 0;
	}
}

// FUNCTION: SADX 0x004fee60
void SetDefaultGravity()
{
	DAT_05b3ebc8 = 0.0f;
	DAT_05b3ebcc = -1.0f;
	DAT_05b3ebd0 = 0.0f;
	DAT_05b3ebdc = 0;
	DAT_05b3ebc4 = 0;
}

// STUB: SADX 0x004feea0
void SetUserGravityXZ(long angx, long angz)
{
}

// STUB: SADX 0x004fefb0
void MakeLandCollLandEntryALL()
{
}

// FUNCTION: SADX 0x004ff1c0
void SetMleriRangeRad(float range)
{
	mleriRangeRad = range;
}

// FUNCTION: SADX 0x004ff1d0
void ResetMleriRangeRad()
{
	mleriRangeRad = 400.0;
}
