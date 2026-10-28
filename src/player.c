#include "decls.h"
#include <math.h>
#include <stdlib.h>
void FUN_004e2cb0(struct task *param_1, struct NJS_POINT3 *param_2, struct taskwk *param_3);
void FUN_004e2ec0(struct taskwk *param_1, struct NJS_POINT3 *param_2);
void PGetAccelerationAirAuto(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp);
void PAdjustAngleY(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, long angy);
long GetPlayerNumber();
extern long PCheckPushAngle(struct taskwk *twp, struct motionwk2 *mwp);
extern void PConvertVector_G2P(struct taskwk *twp, struct NJS_POINT3 *vp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void PConvertVector_P2G(struct taskwk *twp, struct NJS_POINT3 *vp);
extern long PCheckPower(struct taskwk *twp, long *angle, float *stroke);
extern float DAT_05b3ebc8;
extern float DAT_05b3ebcc;
extern float DAT_05b3ebd0;
void PConvertVector_G2P(struct taskwk *twp, struct NJS_POINT3 *vp);
long PCheckPower(struct taskwk *twp, long *angle, float *stroke);
void PAdjustAngleYS(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, long angy);
long PCheckColliAngle(struct taskwk *twp, struct motionwk2 *mwp);
void PlayerFaceModelInterpolateSub(struct obj *objbufp, struct PL_FACE *pfp, short *ip);
void EffectBarrier(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
struct NP_PCHECKDATA {
};
void SetInputP(unsigned char pno, signed char mode);
void SetChangeGameMode(short mode);
unsigned long CheckEditMode();
void DisplayBreathCounterP(struct task *tp);
void DestructBreathCounterP(struct task *tp);
struct mtnjvwk;
void Free(void *mp);
void FUN_004f2630(void *param_1);
extern char DAT_05ba3320[];
static void MomentMuteki(struct task *tp);
static void PlayerSpeedUp(struct task *tp);
static void LoopSECallForTheMode(struct task *tp);
extern long DAT_05ba32e0[4];
void pdVibMxStop(int param_1);
extern char DAT_05ba3320[1];
extern int DAT_05ba32b8[8];
extern int DAT_05baf3a8[8];
void SetVelocityP(unsigned char pno, float x, float y, float z);
void SetFreeCameraMode(long sw);
void FreeTask(struct task *tp);
extern long SCPathPntnmbToOnpos(struct pathtag *tag, unsigned long pntnmb, float *onpos);
static void GamePlayerMissed(struct task *tp);
extern struct PDS_PERIPHERAL DAT_05b932e8[8];
extern int DAT_05ba0bf0;
extern int DAT_05b9f528;
extern long jump_button;
extern struct taskwk *DAT_05baf368[8];
extern int DAT_05baf388[8];
extern int DAT_05ba3328[8];
extern int DAT_05ba9348[8];

// FUNCTION: SADX 0x004da9a0
void SetUpPlayerWork()
{
	int local_8;
	for (local_8 = 0; local_8 < 8; local_8++)
	{
		DAT_05baf388[local_8] = 0;
		DAT_05baf368[local_8] = 0;
		DAT_05ba3328[local_8] = 0;
		DAT_05ba9348[local_8] = 0;
	}
}

// STUB: SADX 0x004dad90
void PDestruct(long num)
{
}

// STUB: SADX 0x004daeb0
void PSetupInput(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004db050
void FUN_004db050(unsigned char pno)
{
}

// STUB: SADX 0x004db110
long PCheckHoldObject(struct taskwk *twp)
{
	return (long)0;
}

// FUNCTION: SADX 0x004db440
long PCheckHoldSwingableObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	struct colliwk *local_8;
	local_8 = twp->cwp->hit_cwp;
	if (local_8 == 0)
	{
		return 0;
	}
	if (*(unsigned char *)((char *)*(void **)((char *)local_8->mytask + 0x20) + 2) != 7)
	{
		return 0;
	}
	return 1;
}

// STUB: SADX 0x004db480
void PShakeObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004db5c0
long PAdjustHoldingPosition(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x004db790
long PCheckPower(struct taskwk *twp, long *angle, float *stroke)
{
	return (long)0;
}

// STUB: SADX 0x004db960
long PCheckBreak(struct taskwk *twp, struct motionwk2 *mwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x004dba30
long PCheckJump(struct taskwk *twp, struct playerwk *pwp)
{
	if (twp->flag & 0x4000)
	{
		return 0;
	}
	if ((DAT_05b932e8[twp->counter.b[0]].press & jump_button) != 0)
	{
		if (CanIMakePanelJump(twp) > 0)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x004dba90
long PCheckJump2(struct taskwk *twp, struct playerwk *pwp)
{
	if ((twp->flag & 0x4000) != 0)
	{
		return 0;
	}
	if ((DAT_05b932e8[twp->counter.b[0]].on & jump_button) != 0)
	{
		if (pwp->jumptimer++ < *(int *)((char *)pwp + 0x9c))
		{
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x004dbb00
long PCheckColliAngle(struct taskwk *twp, struct motionwk2 *mwp)
{
	return (long)0;
}

// STUB: SADX 0x004dbbc0
long PCheckPushAngle(struct taskwk *twp, struct motionwk2 *mwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x004dbca0
long PCheckTargetEnemy(unsigned char pno)
{
	int *local_8;

	if (pno == 0)
		local_8 = &DAT_05ba0bf0;
	else
		local_8 = &DAT_05b9f528;

	if (*local_8 == 0)
		return 0;
	else
		return 1;
}

// STUB: SADX 0x004dbce0
void PLockingOnTargetEnemy(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004ddec0
void PGetAccelerationAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004de880
void PGetAccelerationAirAuto(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004dec40
void PGetAcceleration1D(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004ded90
void PGetAccelerationPushPull(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004df220
void PGetAccelerationFly(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x004df400
void PGetAccelerationGliK(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	long angle;
	float accel;
	struct NJS_POINT3 v;
	if (twp->flag & 0x4000)
	{
		return;
	}
	mwp->acc.y = *(float *)((char *)pwp + 0x114) * 0.949999988079071;
	v = mwp->acc;
	v.x = DAT_05b3ebc8 * *(float *)((char *)pwp + 0x114) + v.x;
	v.y = DAT_05b3ebcc * *(float *)((char *)pwp + 0x114) + v.y;
	v.z = DAT_05b3ebd0 * *(float *)((char *)pwp + 0x114) + v.z;
	PConvertVector_G2P(twp, &v);
	v.x = *(float *)((char *)pwp + 0xf0) * 0.5 * *(float *)((char *)pwp + 0x38) + v.x;
	v.y = *(float *)((char *)pwp + 0xf4) * 0.5 * *(float *)((char *)pwp + 0x3c) + v.y;
	v.z = *(float *)((char *)pwp + 0xf8) * 0.5 * *(float *)((char *)pwp + 0x40) + v.z;
	if (PCheckPower(twp, &angle, &accel) == 0)
	{
		accel = 0.0;
		*(int *)((char *)mwp + 0x20) = twp->ang.y;
	}
	else
	{
		accel = *(float *)((char *)pwp + 0xdc) * accel;
		*(int *)((char *)mwp + 0x20) = angle;
		PAdjustAngleY(twp, mwp, pwp, *(int *)((char *)mwp + 0x20));
	}
	v.x = v.x + accel;
	pwp->acc = v;
}

// STUB: SADX 0x004df580
void FUN_004df580(struct task *tp, int param_2, struct NJS_POINT3 *out)
{
}

// STUB: SADX 0x004e0580
void FUN_004e0580(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e16d0
void PGetInertia(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e1920
void PGetGravity(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e1c60
void PRotatedByGravity(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e1e40
void PRotatedByGravityS(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e2010
void PRotatedByGravityAsPinball(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e22a0
void PResetAngle(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x004e23a0
void PResetAngleForBuilding(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	struct NJS_POINT3 v2;
	float local_18;
	v2 = pwp->spd;
	local_18 = v2.x * v2.x + v2.y * v2.y + v2.z * v2.z;
	if (*(float *)((char *)pwp + 0xd0) * *(float *)((char *)pwp + 0xd0) < local_18)
	{
		return;
	}
	PConvertVector_P2G(twp, &v2);
	twp->ang.x = AdjustAngle(twp->ang.x, 0, 0x800);
	twp->ang.z = AdjustAngle(twp->ang.z, 0xc000, 0x800);
	PConvertVector_G2P(twp, &v2);
	pwp->spd = v2;
}

#pragma optimize("", off)
// STUB: SADX 0x004e2480
void PAdjustAngleY(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, long angy)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004e2770
void PAdjustAngleYQ(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, long angy)
{
	struct NJS_POINT3 v2;
	v2 = pwp->spd;
	PConvertVector_P2G(twp, &v2);
	twp->ang.y = AdjustAngle(twp->ang.y, angy, 0x2000);
	PConvertVector_G2P(twp, &v2);
	pwp->spd = v2;
}

// STUB: SADX 0x004e2800
void PAdjustAngleYS(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, long angy)
{
}

// STUB: SADX 0x004e2950
void PGetSpeed(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x004e2cb0
void FUN_004e2cb0(struct task *param_1, struct NJS_POINT3 *param_2, struct taskwk *param_3)
{
	if (*(short *)((char *)param_1 + 4) & 0x800)
	{
		if (*(float *)((char *)param_3 + 0xa4) < param_2->y)
		{
			param_2->y = *(float *)((char *)param_3 + 0xa4);
		}
		if (param_2->y < -*(float *)((char *)param_3 + 0xa4))
		{
			param_2->y = -*(float *)((char *)param_3 + 0xa4);
		}
		if (*(float *)((char *)param_3 + 0xa4) < *(float *)((char *)param_2 + 0xc))
		{
			*(float *)((char *)param_2 + 0xc) = *(float *)((char *)param_3 + 0xa4);
		}
		if (*(float *)((char *)param_2 + 0xc) < -*(float *)((char *)param_3 + 0xa4))
		{
			*(float *)((char *)param_2 + 0xc) = -*(float *)((char *)param_3 + 0xa4);
		}
		if (*(float *)((char *)param_3 + 0xa8) < param_2->z)
		{
			param_2->z = *(float *)((char *)param_3 + 0xa8);
		}
		if (param_2->z < -*(float *)((char *)param_3 + 0xa8))
		{
			param_2->z = -*(float *)((char *)param_3 + 0xa8);
		}
	}
	else
	{
		if (*(float *)((char *)param_3 + 0xa4) < param_2->y)
		{
			param_2->y = *(float *)((char *)param_3 + 0xa4);
		}
		if (param_2->y < -*(float *)((char *)param_3 + 0xa4))
		{
			param_2->y = -*(float *)((char *)param_3 + 0xa4);
		}
		if (*(float *)((char *)param_3 + 0xa4) < *(float *)((char *)param_2 + 0xc))
		{
			*(float *)((char *)param_2 + 0xc) = *(float *)((char *)param_3 + 0xa4);
		}
		if (*(float *)((char *)param_2 + 0xc) < -*(float *)((char *)param_3 + 0xa4))
		{
			*(float *)((char *)param_2 + 0xc) = -*(float *)((char *)param_3 + 0xa4);
		}
		if (*(float *)((char *)param_3 + 0xa8) < param_2->z)
		{
			param_2->z = *(float *)((char *)param_3 + 0xa8);
		}
		if (param_2->z < -*(float *)((char *)param_3 + 0xa8))
		{
			param_2->z = -*(float *)((char *)param_3 + 0xa8);
		}
	}
	return;
}

// STUB: SADX 0x004e2ec0
void FUN_004e2ec0(struct taskwk *twp, struct NJS_POINT3 *v)
{
}

// STUB: SADX 0x004e2fc0
void PGetSpeed1D(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x004e3110
void FUN_004e3110(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	PGetPushSpeed(param_1, param_2, param_3);
}

#pragma optimize("", off)
// STUB: SADX 0x004e3130
void PGetPushSpeed(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004e3420
void FUN_004e3420(struct task *param_1, struct NJS_POINT3 *param_2, struct taskwk *param_3)
{
	NJS_POINT3 local_14;
	*(NJS_POINT3 *)((char *)param_3 + 0x38) = param_3->scl;
	local_14 = *(NJS_POINT3 *)((char *)param_3 + 0x38);
	PConvertVector_P2G((struct taskwk *)param_1, &local_14);
	*(NJS_POINT3 *)((char *)param_2 + 4) = local_14;
	FUN_004e2cb0(param_1, param_2, param_3);
}

// STUB: SADX 0x004e34b0
void PGetSpeedGliK(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e4110
void FUN_004e4110(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004e60d0
long PSSGCollisionedWall(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, struct csts *cp, struct NJS_POINT3 *last_pos, struct NJS_POINT3 *center, long ret, long attr)
{
	return (long)0;
}

// STUB: SADX 0x004e64d0
void PSSGCollisionGetCenterAndError(struct motionwk2 *mwp, struct playerwk *pwp, struct csts *cp, struct NJS_POINT3 *vp)
{
}

// STUB: SADX 0x004e67d0
void PSSGCollisionAdjustAngleXZ(struct taskwk *twp, struct playerwk *pwp, struct csts *cp)
{
}

// STUB: SADX 0x004e6a00
void PSSGCollisionForceWorkEffect(struct taskwk *twp, struct playerwk *pwp, struct csts *cp, struct NJS_POINT3 *vec)
{
}

// FUNCTION: SADX 0x004e6b90
void FUN_004e6b90(int param_1, int param_2, int param_3)
{
	*(float *)(param_1 + 0x20) = *(float *)(param_3 + 0x3c) * 3.0f + *(float *)(param_1 + 0x20);
	*(float *)(param_1 + 0x24) = *(float *)(param_3 + 0x40) * 3.0f + *(float *)(param_1 + 0x24);
	*(float *)(param_1 + 0x28) = *(float *)(param_3 + 0x44) * 3.0f + *(float *)(param_1 + 0x28);
	*(float *)(param_2 + 4) = *(float *)(param_3 + 0x3c) * 2.0f + *(float *)(param_2 + 4);
	*(float *)(param_2 + 0xc) = *(float *)(param_3 + 0x44) * 2.0f + *(float *)(param_2 + 0xc);
}

// STUB: SADX 0x004e6c10
void PSSGCollisionGetLandFriction(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, unsigned long attr)
{
}

// STUB: SADX 0x004e7240
long PSSGCollisionCheckGround(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, struct csts *cp)
{
	return (long)0;
}

// STUB: SADX 0x004ea1a0
long PSSGCollisionedWallNoBrake(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, struct csts *cp, struct NJS_POINT3 *last_pos, struct NJS_POINT3 *center, long ret, long attr)
{
	return (long)0;
}

// STUB: SADX 0x004eadd0
void PSRunAlongWallForPinball(struct taskwk *twp, struct playerwk *pwp, struct csts *cp, struct NJS_POINT3 *vp)
{
}

// STUB: SADX 0x004eb550
long PSetPositionOn1D(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

#pragma optimize("", off)
// STUB: SADX 0x004ebeb0
void PConvertVector_G2P(struct taskwk *twp, struct NJS_POINT3 *vp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x004ebf90
void PConvertVector_P2G(struct taskwk *twp, struct NJS_POINT3 *vp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x004ec070
void PConvertVector_G2N(struct NJS_POINT3 *np, struct NJS_POINT3 *vp, long angy)
{
}

// STUB: SADX 0x004ec160
void PConvertVector_N2G(struct NJS_POINT3 *np, struct NJS_POINT3 *vp, long angy)
{
}

// STUB: SADX 0x004ec250
void PResetPosition(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004ec460
void PResetPositionForBuilding(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x004ed0e0
void PSetMotion_Next(struct mtnjvwk *mjp, unsigned short patno)
{
}

// FUNCTION: SADX 0x004ed170
void PSetMotion_SetStartFrame(struct mtnjvwk *mjp)
{
	if (mjp->mtnmode == 6 || 7 == mjp->mtnmode)
	{
		mjp->nframe = (float)mjp->plactptr[mjp->action].actptr->motion->nbFrame - 1.0;
	}
	else if (!(!(mjp->mtnmode == 3 || mjp->mtnmode == 10 || mjp->mtnmode == 9 || mjp->mtnmode == 0xc)))
	{
		mjp->nframe = mjp->start_frame;
		mjp->start_frame = 0.0;
	}
	else
	{
		mjp->nframe = 0.0;
	}
}

// STUB: SADX 0x004ed210
void FUN_004ed210(struct mtnjvwk *mjp)
{
}

// STUB: SADX 0x004ee220
void PTerminateInterpolateMotion(struct mtnjvwk *mjp)
{
}

// FUNCTION: SADX 0x004eef80
void PAdjustAngleFacingTo(struct pheadeyewk *phewp)
{
	long local_8;
	local_8 = AdjustAngle(phewp->angy_ahead, phewp->angy_head, 0x1000);
	if (local_8 > 0x8000)
	{
		local_8 = local_8 | 0xffff0000;
	}
	if (local_8 > phewp->angy_head_max)
	{
		local_8 = phewp->angy_head_max;
	}
	else if (local_8 < phewp->angy_head_min)
	{
		local_8 = phewp->angy_head_min;
	}
	phewp->angy_ahead = local_8;
	phewp->headobjptr->ang[1] = phewp->angy_ahead & 0xffff;
	local_8 = AdjustAngle(phewp->angz_ahead, phewp->angz_head, 0x1000);
	if (local_8 > 0x8000)
	{
		local_8 = local_8 | 0xffff0000;
	}
	if (local_8 > phewp->angz_head_max)
	{
		local_8 = phewp->angz_head_max;
	}
	else if (local_8 < phewp->angz_head_min)
	{
		local_8 = phewp->angz_head_min;
	}
	phewp->angz_ahead = local_8;
	phewp->headobjptr->ang[2] = phewp->angz_ahead & 0xffff;
}

// STUB: SADX 0x004ef080
void PAdjustAngleStaringEyes(struct pheadeyewk *phewp)
{
}

// FUNCTION: SADX 0x004ef210
void PlayerFaceMotionEnd(struct task *tp)
{
	struct motionwk *local_8;
	local_8 = tp->mwp;
	if (local_8 != 0)
	{
		if (*(int *)((char *)local_8 + 0x10) != 0)
		{
			*(int *)(*(int *)((char *)local_8 + 0x10) + 0x30) = *(int *)((char *)local_8 + 0x14);
			*(int *)((char *)local_8 + 0xc) = 0;
		}
	}
}

// STUB: SADX 0x004ef550
void PlayerFaceModelInterpolateSub(struct obj *objbufp, struct PL_FACE *pfp, short *ip)
{
}

// FUNCTION: SADX 0x004ef640
void PFaceChange(unsigned char pno, long face)
{
	int local_8;
	if (DAT_05ba9348[pno] != 0)
	{
		local_8 = *(int *)((char *)DAT_05ba9348[pno] + 0x70);
		if (local_8 != 0)
		{
			*(int *)((char *)local_8 + 0xc) = *(int *)((char *)faceTbl + face * 4);
		}
	}
}

// FUNCTION: SADX 0x004ef680
void PFaceCancel(unsigned char pno)
{
	int *local_8;
	if (DAT_05ba9348[pno] != 0)
	{
		local_8 = *(int **)(DAT_05ba9348[pno] + 0x70);
		if (local_8 != 0)
		{
			*(int *)((char *)local_8 + 0xc) = 0;
		}
	}
}

// FUNCTION: SADX 0x004ef6c0
void PSetCrashEffect(struct taskwk *twp)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 6, EffectCrash);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)twp + 8);
	}
}

// STUB: SADX 0x004ef700
void PSetRippleEffect(unsigned char pno, struct NJS_POINT3 *pp, long *ap)
{
}

// STUB: SADX 0x004ef840
void PSetSplashEffect(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x004efc80
void PSetLoopSECallForTheMode(long SE, unsigned char pno, short mode)
{
	struct task *local_8;
	local_8 = CreateElementalTask(8, 6, LoopSECallForTheMode);
	if (local_8)
	{
		*(long *)((char *)local_8->awp + 0) = SE;
		*(unsigned char *)((char *)local_8->awp + 4) = pno;
		*(short *)((char *)local_8->awp + 6) = mode;
	}
}

// STUB: SADX 0x004efcd0
static void LoopSECallForTheMode(struct task *tp)
{
}

// FUNCTION: SADX 0x004f0020
void KillHimP(unsigned char pno)
{
	short *local_8;
	local_8 = (short *)DAT_05baf368[pno];
	if (*(unsigned char *)((char *)local_8 + 8) == 1)
	{
		return;
	}
	if (CheckEditMode() == 0)
	{
		*(short *)((char *)local_8 + 4) = *(short *)((char *)local_8 + 4) | 0x1000;
		*(unsigned char *)((char *)local_8 + 1) = 0x32;
		*(short *)((char *)DAT_05ba9348[pno] + 6) = *(short *)((char *)DAT_05ba9348[pno] + 6) | 0x4000;
		CreateElementalTask(8, 0, GamePlayerMissed);
	}
}

// FUNCTION: SADX 0x004f00a0
static void GamePlayerMissed(struct task *tp)
{
	if (tp->awp->work.ul[0]++ > 0x78)
	{
		SetChangeGameMode(2);
		if (tp->ptp != NULL)
		{
			tp->ptp->twp->flag |= 4;
		}
		TempEraseSound();
		FreeTask(tp);
	}
	else
	{
		if (CheckEditMode() != 0)
		{
			FreeTask(tp);
		}
	}
}

// FUNCTION: SADX 0x004f0120
void KillHimByFallingDownP(unsigned char pno)
{
	struct task *local_8;

	local_8 = CreateElementalTask(8, 0, GamePlayerMissed);
	local_8->dest = (void (*)(struct task *))FUN_005b5aa0;
	ExecFallingDownP(pno);
}

#pragma optimize("", off)
// STUB: SADX 0x004f0160
void ExecFallingDownP(unsigned char pno)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004f02a0
void FUN_004f02a0(struct task *param_1, unsigned char param_2)
{
	struct task *local_8;
	local_8 = CreateChildTask(8, GamePlayerMissed, param_1);
	local_8->dest = (void (*)(struct task *))FUN_005b5aa0;
	ExecFallingDownP(param_2);
}

// STUB: SADX 0x004f02e0
void BreathCounterP(struct task *tp)
{
}

// STUB: SADX 0x004f04d0
void DisplayBreathCounterP(struct task *tp)
{
}

// FUNCTION: SADX 0x004f0610
void DestructBreathCounterP(struct task *tp)
{
	BGM_Replay();
}

// FUNCTION: SADX 0x004f0620
void RunAlongPathP(unsigned char pno, struct pathtag *pp)
{
	short *local_8;
	local_8 = (short *)DAT_05baf368[pno];
	*(short *)((char *)local_8 + 4) |= 0x1000;
	*(char *)((char *)local_8 + 1) = 1;
	*(struct pathtag **)((char *)local_8 + 0x10) = pp;
	*(float *)((char *)DAT_05ba9348[pno] + 0x38) += 5.0;
}

// FUNCTION: SADX 0x004f0680
void RunWithSeeingPathP(unsigned char pno, struct pathtag *pp)
{
	struct pathtag *local_8;

	local_8 = (struct pathtag *)DAT_05baf368[pno];
	if (local_8 == 0)
	{
		return;
	}
	*(short *)((char *)local_8 + 4) = *(short *)((char *)local_8 + 4) | 0x1000;
	*(unsigned char *)((char *)local_8 + 1) = 0x1a;
	*(void **)((char *)local_8 + 0x10) = pp;
	SCPathPntNearToOnpos(pp, (struct NJS_POINT3 *)((char *)local_8 + 0x20), 0, (float *)(DAT_05ba9348[pno] + 0x18));
}

// FUNCTION: SADX 0x004f06f0
void HangDownFromPathP(unsigned char pno, struct pathtag *pp, long point)
{
	char *local_cg;
	char *local_8g;

	local_cg = (char *)DAT_05baf368[pno];
	local_8g = (char *)DAT_05ba9348[pno];
	*(short *)(local_cg + 4) = *(short *)(local_cg + 4) | 0x1000;
	local_cg[1] = 0x1d;
	*(int *)(local_cg + 0x10) = (int)pp;
	*(short *)(local_8g + 0x14) = (short)point;
	SCPathPntnmbToOnpos(pp, point, (float *)(local_8g + 0x18));
}

// FUNCTION: SADX 0x004f0760
void LadderingPathP(unsigned char pno, struct pathtag *pp, long point, struct Angle3 *ang)
{
	char *local_cg;
	char *local_8g;

	local_cg = (char *)DAT_05baf368[pno];
	local_8g = (char *)DAT_05ba9348[pno];
	*(short *)(local_cg + 4) = *(short *)(local_cg + 4) | 0x1000;
	local_cg[1] = 0x1f;
	*(int *)(local_cg + 0x10) = (int)pp;
	*(short *)(local_8g + 0x14) = (short)point;
	SCPathPntnmbToOnpos(pp, point, (float *)(local_8g + 0x18));
	SetRotationP(pno, ang->x, ang->y, ang->z);
}

// FUNCTION: SADX 0x004f07f0
int FUN_004f07f0(int param_1)
{
	int local_8g;
	short *local_cj;
	int local_10;

	local_10 = 0;
	for (local_8g = 0; local_8g < 2; local_8g++)
	{
		local_cj = (short *)DAT_05baf368[local_8g];
		if (local_cj != 0)
		{
			if (((*(short *)((char *)local_cj + 4)) & 0x2000) != 0)
			{
				if (*(int *)((char *)local_cj + 0x10) == param_1)
				{
					local_10 += local_8g + 1;
				}
			}
		}
	}
	return local_10;
}

// FUNCTION: SADX 0x004f0860
void FUN_004f0860(unsigned char param_1, float param_2, float param_3)
{
	if (DAT_05baf368[param_1] == 0)
	{
		return;
	}
	int local_8;
	local_8 = (int)DAT_05baf368[param_1]->ewp;
	*(unsigned char *)(local_8 + 0x24) = 2;
	*(float *)(local_8 + 0x28) = param_2;
	*(float *)(local_8 + 0x30) = param_3;
	*(float *)(local_8 + 0x34) = 0.0f;
	*(float *)(local_8 + 0x38) = 0.0f;
	DAT_05baf368[param_1]->flag |= 0x4000;
}

// FUNCTION: SADX 0x004f08e0
void SetAutoPilotForBreakP(unsigned char pno)
{
	if (DAT_05baf368[pno] == 0)
	{
		return;
	}
	int local_8;
	local_8 = (int)DAT_05baf368[pno]->ewp;
	*(unsigned char *)(local_8 + 0x24) = 1;
	DAT_05baf368[pno]->flag |= 0x4000;
}

// FUNCTION: SADX 0x004f0940
void SetAutoPilotForYRotationP(unsigned char pno, long y)
{
	SetRotationP(pno, DAT_05baf368[pno]->ang.x, y, DAT_05baf368[pno]->ang.z);
	*(unsigned char *)((char *)DAT_05baf368[pno]->ewp + 0x24) = 0;
}

// FUNCTION: SADX 0x004f0990
void CancelAutoPilotP(unsigned char pno)
{
	*(char *)((char *)DAT_05baf368[pno]->ewp + 0x24) = 0;
}

// FUNCTION: SADX 0x004f09b0
void SetLookingTaskP(unsigned char pno, struct task *ttp, struct NJS_POINT3 *offset)
{
	int local_8;
	if (DAT_05baf368[pno] == 0)
	{
		return;
	}
	local_8 = (int)DAT_05baf368[pno]->ewp;
	*(unsigned char *)((char *)local_8 + 4) = 3;
	*(int *)((char *)local_8 + 0x20) = (int)ttp;
	if (offset != 0)
	{
		*(float *)((char *)local_8 + 0x14) = offset->x;
		*(float *)((char *)local_8 + 0x18) = offset->y;
		*(float *)((char *)local_8 + 0x1c) = offset->z;
	}
}

// FUNCTION: SADX 0x004f0a20
void SetLookingPointP(unsigned char pno, struct NJS_POINT3 *point)
{
	if (DAT_05baf368[pno] == 0)
		return;
	int local_8 = (int)DAT_05baf368[pno]->ewp;
	*(unsigned char *)((char *)local_8 + 4) = 2;
	if (point == 0)
		return;
	*(float *)((char *)local_8 + 0x14) = point->x;
	*(float *)((char *)local_8 + 0x18) = point->y;
	*(float *)((char *)local_8 + 0x1c) = point->z;
}

// FUNCTION: SADX 0x004f0a80
void SetLookingAngleP(unsigned char pno, long *ang)
{
	long *local_8;
	if (DAT_05baf368[pno] == 0)
		return;
	local_8 = (long *)DAT_05baf368[pno]->ewp;
	*(char *)(local_8 + 1) = 1;
	if (ang == 0)
		return;
	local_8[2] = ang[0];
	local_8[3] = ang[1];
	local_8[4] = ang[2];
}

// FUNCTION: SADX 0x004f0ae0
void CancelLookingAtP(unsigned char pno)
{
	if (DAT_05baf368[pno] == 0)
	{
		return;
	}
	int local_8;
	local_8 = (int)DAT_05baf368[pno]->ewp;
	*(unsigned char *)(local_8 + 4) = 0;
}

// FUNCTION: SADX 0x004f0b10
void KeepPlayersEyesOnTheTaskP(unsigned char pno, struct task *ttp, unsigned long count)
{
	struct NJS_POINT3 local_18m;
	struct task *local_8g;

	if (DAT_05baf368[pno] == 0)
	{
		return;
	}
	if (ttp == 0)
	{
		return;
	}
	local_8g = CreateElementalTask(8, 5, PlayerLookingAt);
	if (local_8g != 0)
	{
		local_18m.z = 0.0f;
		local_18m.y = local_18m.z;
		local_18m.x = local_18m.y;
		local_8g->dest = PlayerLookingAtDestructor;
		local_8g->awp->work.ub[0] = pno;
		local_8g->awp->work.ul[2] = count;
		SetLookingTaskP(pno, ttp, &local_18m);
	}
}

// FUNCTION: SADX 0x004f0bb0
void PlayerLookingAtDestructor(struct task *tp)
{
	CancelLookingAtP(*(unsigned char *)tp->awp);
}

// STUB: SADX 0x004f0bd0
void PlayerLookingAt(struct task *tp)
{
}

// FUNCTION: SADX 0x004f0c20
void KeepPlayersEyesOnThePointP(unsigned char pno, struct NJS_POINT3 *point, unsigned long count)
{
	struct task *local_8g;

	if (DAT_05baf368[pno] == 0)
	{
		return;
	}
	if (point == 0)
	{
		return;
	}
	local_8g = CreateElementalTask(8, 5, PlayerLookingAt);
	if (local_8g != 0)
	{
		local_8g->dest = PlayerLookingAtDestructor;
		local_8g->awp->work.ub[0] = pno;
		local_8g->awp->work.ul[2] = count;
		SetLookingPointP(pno, point);
	}
}

// FUNCTION: SADX 0x004f0c90
void FUN_004f0c90(unsigned char param_1, int param_2)
{
	short *local_8;

	local_8 = (short *)DAT_05baf368[param_1];
	if ((local_8[2] & 0x800) == 0)
	{
		local_8[2] |= 0x1000;
		((char *)local_8)[1] = 0x20;
		*(int *)((char *)DAT_05ba9348[param_1] + 0x68) = param_2;
	}
}

// FUNCTION: SADX 0x004f0ce0
void FUN_004f0ce0(unsigned char param_1, int param_2)
{
	char *local_8 = (char *)DAT_05baf368[param_1];
	if ((*(short *)(local_8 + 4) & 0x800) == 0)
	{
		SetFreeCameraMode(0);
		*(short *)(local_8 + 4) |= 0x1000;
		*(char *)(local_8 + 1) = 0x1e;
		*(int *)(DAT_05ba9348[param_1] + 0x68) = param_2;
	}
}

// FUNCTION: SADX 0x004f0d40
void CrashPlayerP(unsigned char pno, float x, float y, float z)
{
	short *local_8;

	local_8 = (short *)DAT_05baf368[pno];
	*(short *)((char *)local_8 + 4) |= 0x1000;
	*(unsigned char *)((char *)local_8 + 1) = 0x23;
	SetRotationByVectorP(pno, -x, 0.0f, -z);
	SetVelocityP(pno, x, y, z);
}

// FUNCTION: SADX 0x004f0dc0
void SetInputP(unsigned char pno, signed char mode)
{
	short *local_8;
	local_8 = (short *)DAT_05baf368[pno];
	if (local_8 != 0)
	{
		*(short *)((char *)local_8 + 4) = *(short *)((char *)local_8 + 4) | 0x1000;
		*(char *)((char *)local_8 + 1) = (char)mode;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x004f0e00
void SetVelocityP(unsigned char pno, float x, float y, float z)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004f0f00
void SetSpringVelocityP(unsigned char pno, float x, float y, float z)
{
	short *local_8;

	local_8 = (short *)DAT_05baf368[pno];
	local_8[2] |= 0x1000;
	((char *)local_8)[1] = 3;
	SetVelocityP(pno, x, y, z);
}

// FUNCTION: SADX 0x004f0f60
void SetTrampolineVelocityP(unsigned char pno, unsigned char time, float x, float y, float z)
{
	int local_8;

	local_8 = (int)DAT_05baf368[pno];
	*(short *)((char *)local_8 + 4) |= 0x1000;
	if (time == 3)
	{
		*(char *)((char *)local_8 + 1) = 8;
	}
	else if (time == 2)
	{
		*(char *)((char *)local_8 + 1) = 7;
	}
	else
	{
		*(char *)((char *)local_8 + 1) = 6;
	}
	SetVelocityP(pno, x, y, z);
}

// STUB: SADX 0x004f0fe0
void SetVelocityYAndRotationAndNoconTimeP(unsigned char pno, float y, long *ang, long tm)
{
}

// STUB: SADX 0x004f10d0
void SetParabolicMotionP(unsigned char pno, float spd, struct NJS_POINT3 *v)
{
}

// STUB: SADX 0x004f11f0
void SetVelocityAndRotationAndNoconTimeP(unsigned char pno, struct NJS_POINT3 *v, long *ang, long tm)
{
}

// FUNCTION: SADX 0x004f12d0
void SetVelocityAndRotationAndNoconTimeWithSpinDashP(unsigned char pno, struct NJS_POINT3 *v, long *ang, long tm)
{
	struct NJS_POINT3 w;
	struct taskwk *local_20;
	int local_1c;
	int local_18;
	local_20 = DAT_05baf368[pno];
	local_18 = DAT_05ba3328[pno];
	local_1c = DAT_05ba9348[pno];
	*(short *)((char *)local_1c + 0xa) = (short)tm;
	local_20->flag = local_20->flag | 0x1000;
	local_20->smode = 0x19;
	*(struct NJS_POINT3 *)((char *)local_1c + 0x38) = *v;
	local_20->ang.x = *ang;
	local_20->ang.y = 0x4000 - ang[1];
	*(int *)((char *)local_18 + 0x20) = local_20->ang.y;
	local_20->ang.z = ang[2];
	w = *v;
	PConvertVector_P2G(local_20, &w);
	*(struct NJS_POINT3 *)((char *)local_18 + 4) = w;
}

// FUNCTION: SADX 0x004f13d0
void SetRotationP(unsigned char pno, long angx, long angy, long angz)
{
	char *local_cg;
	char *local_8g;

	local_cg = (char *)DAT_05baf368[pno];
	local_8g = (char *)DAT_05ba3328[pno];
	*(int *)(local_cg + 0x14) = angx;
	*(int *)(local_cg + 0x18) = 0x4000 - angy;
	*(int *)(local_8g + 0x20) = *(int *)(local_cg + 0x18);
	*(int *)(local_cg + 0x1c) = angz;
}

#pragma optimize("", off)
// STUB: SADX 0x004f1430
void SetRotationByVectorP(unsigned char pno, float x, float y, float z)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004f15e0
void SetAscendPowerP(unsigned char pno, float x, float y, float z)
{
	short *local_8;

	local_8 = (short *)DAT_05baf368[pno];
	*(short *)(local_8 + 2) |= 0x1000;
	*(unsigned char *)((char *)local_8 + 1) = 0xb;
	SetAccelerationP(pno, x, y, z);
}

// FUNCTION: SADX 0x004f1640
void SetPowerP(unsigned char pno, float x, float y, float z)
{
	int *local_8;

	local_8 = (int *)DAT_05ba9348[pno];
	x = x / *(float *)((char *)local_8 + 0x114);
	y = y / *(float *)((char *)local_8 + 0x114);
	z = z / *(float *)((char *)local_8 + 0x114);
	SetAccelerationP(pno, x, y, z);
}

// FUNCTION: SADX 0x004f16b0
void SetAccelerationP(unsigned char pno, float x, float y, float z)
{
	int local_8 = DAT_05ba3328[pno];
	*(float *)((char *)local_8 + 0x10) = x;
	*(float *)((char *)local_8 + 0x14) = y;
	*(float *)((char *)local_8 + 0x18) = z;
}

// STUB: SADX 0x004f16f0
void SetPositionP(unsigned char pno, float x, float y, float z)
{
}

// FUNCTION: SADX 0x004f17a0
void ChangeModePlaceWithTrampolineP(unsigned char pno, unsigned char time)
{
	short *local_8 = (short *)DAT_05baf368[pno];
	*(short *)(local_8 + 2) = *(short *)(local_8 + 2) | 0x1000;
	if (time == 3)
	{
		*(char *)((char *)local_8 + 1) = 0xa;
	}
	else if (time == 2)
	{
		*(char *)((char *)local_8 + 1) = 9;
	}
	else
	{
		*(char *)((char *)local_8 + 1) = 0xc;
	}
}

// FUNCTION: SADX 0x004f1800
void GetOutOfCartP(unsigned char pno, float x, float y, float z)
{
	char *local_8;

	local_8 = (char *)DAT_05baf368[pno];
	*(short *)(local_8 + 4) |= 0x1000;
	*(char *)(local_8 + 1) = 0x1c;
	SetVelocityP(pno, x, y, z);
}

// STUB: SADX 0x004f1860
long CheckCollisionP(struct NJS_POINT3 *vp, float d)
{
	return (long)0;
}

// STUB: SADX 0x004f1980
long CheckCollisionCylinderP(struct NJS_POINT3 *vp, float r, float h)
{
	return (long)0;
}

// FUNCTION: SADX 0x004f1a60
long GetPlayerCharacterName(unsigned char pno)
{
	short *local_8;
	local_8 = (short *)DAT_05baf368[pno];
	if (local_8 == 0)
	{
		return GetPlayerNumber();
	}
	return *(unsigned char *)((char *)local_8 + 9);
}

// STUB: SADX 0x004f1a90
long GetPlayerRunningSpeed(unsigned char pno, float *v)
{
	return (long)0;
}

// STUB: SADX 0x004f1af0
long GetPlayerPosition(unsigned char pno, unsigned char frame, struct NJS_POINT3 *pos, long *ang)
{
	return (long)0;
}

// STUB: SADX 0x004f1bb0
long SetPlayerPosition(unsigned char pno, unsigned char frame, struct NJS_POINT3 *pos, long *ang)
{
	return (long)0;
}

// FUNCTION: SADX 0x004f1c70
struct task *GetPlayerTaskPointer(unsigned char pno)
{
	return (struct task *)DAT_05baf388[pno];
}

// FUNCTION: SADX 0x004f1ce0
struct playerwk *GetPlayerWorkPointer(unsigned char pno)
{
	return (struct playerwk *)DAT_05ba9348[pno];
}

// FUNCTION: SADX 0x004f1cf0
long CountCharacters()
{
	int local_cg = 0;
	int local_8g = 0;
	for (; local_8g < 8; local_8g++)
	{
		if (DAT_05baf388[local_8g])
		{
			local_cg++;
		}
	}
	return local_cg;
}

// STUB: SADX 0x004f1d40
long GetTheNearestPlayerNumber(struct NJS_POINT3 *pos)
{
	return (long)0;
}

// FUNCTION: SADX 0x004f1df0
long GetRivalPlayerNumber(unsigned char pno)
{
	int local_8g;
	int local_cg;

	if (DAT_05baf368[pno]->id == 3)
	{
		local_8g = 1;
	}
	else
	{
		local_8g = 3;
	}
	for (local_cg = 0; local_cg < 8; local_cg++)
	{
		if (DAT_05baf368[local_cg] != 0 && DAT_05baf368[local_cg]->id == local_8g)
		{
			return local_cg;
		}
	}
	return -1;
}

// FUNCTION: SADX 0x004f1e60
long CheckPlayerRideOnMobileLandObjectP(unsigned char pno, struct task *ttp)
{
	struct task *local_cg;
	struct task *local_8g;

	local_cg = (struct task *)DAT_05baf368[pno];
	local_8g = (struct task *)DAT_05ba9348[pno];
	if (local_8g == 0 || local_cg == 0)
	{
		return 0;
	}
	if ((*(short *)((char *)local_cg + 4) & 1) != 0 && *(struct task **)((char *)local_8g + 0x6c) == ttp)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004f1ec0
void PlayerDisable(unsigned char pno)
{
	int local_8;
	local_8 = DAT_05baf388[pno];
	if (local_8 == 0)
	{
		return;
	}
	DAT_05ba32b8[pno] = *(int *)(local_8 + 0x10);
	DAT_05baf3a8[pno] = *(int *)(local_8 + 0x14);
	*(int *)(local_8 + 0x10) = 0;
	*(int *)(local_8 + 0x14) = 0;
}

// FUNCTION: SADX 0x004f1f20
void PlayerEnable(unsigned char pno)
{
	int local_8;
	local_8 = DAT_05baf388[pno];
	if (local_8 == 0)
	{
		return;
	}
	*(int *)(local_8 + 0x10) = DAT_05ba32b8[pno];
	*(int *)(local_8 + 0x14) = DAT_05baf3a8[pno];
}

// FUNCTION: SADX 0x004f1f60
void GetSpeedUpP(unsigned char pno)
{
	struct task *local_8;

	if (pno >= 1 && (pno > 7 || DAT_05baf368[pno] == 0))
	{
		pno = 0;
	}
	local_8 = CreateElementalTask(8, 2, PlayerSpeedUp);
	if (local_8 != 0)
	{
		*(unsigned char *)(local_8->awp) = pno;
	}
}

// FUNCTION: SADX 0x004f1fc0
void PlayerSpeedUp(struct task *tp)
{
	int local_8;
	local_8 = DAT_05ba9348[tp->awp->work.ub[0]];
	if (local_8 == 0)
	{
		FreeTask(tp);
	}
	else
	{
		tp->awp->work.f[1] = *(float *)(local_8 + 0xd8);
		tp->awp->work.f[2] = *(float *)(local_8 + 0xac);
		tp->awp->work.f[3] = *(float *)(local_8 + 0x104);
		*(float *)(local_8 + 0xd8) = *(float *)(local_8 + 0xd8) * 2.0f;
		*(float *)(local_8 + 0xac) = *(float *)(local_8 + 0xac) * 2.0f;
		*(float *)(local_8 + 0x104) = *(float *)(local_8 + 0x104) * 2.0f;
		if (((DAT_05b9d724 << 8) | DAT_05b9d744) != 0x401)
		{
			Jingle_Play(0x55);
		}
		tp->exec = PlayerSpeedUpMan;
		tp->dest = PlayerSpeedUpDest;
	}
}

// FUNCTION: SADX 0x004f20a0
void PlayerSpeedUpMan(struct task *tp)
{
	int local_8;

	local_8 = DAT_05ba9348[tp->awp->work.ub[0]];
	if (local_8 == 0 || tp->awp->work.uw[1]++ >= 0x258)
	{
		FreeTask(tp);
	}
}

// FUNCTION: SADX 0x004f2100
void PlayerSpeedUpDest(struct task *tp)
{
	int local_8;

	local_8 = DAT_05ba9348[*(unsigned char *)tp->awp];
	if (local_8 != 0)
	{
		*(float *)(local_8 + 0xd8) = tp->awp->work.f[1];
		*(float *)(local_8 + 0xac) = tp->awp->work.f[2];
		*(float *)(local_8 + 0x104) = tp->awp->work.f[3];
	}
}

// FUNCTION: SADX 0x004f2160
void GetThunderBarrierP(unsigned char pno)
{
	struct task *local_cg;
	struct task *local_8g;

	if (pno >= 1 && pno > 7 && DAT_05baf368[pno] == 0)
	{
		pno = 0;
	}
	local_8g = (struct task *)DAT_05ba9348[pno];
	if (local_8g == 0)
	{
		return;
	}
	if ((*(short *)((char *)local_8g + 6) & 2) != 0)
	{
		return;
	}
	local_cg = CreateElementalTask(2, 2, EffectThunderBarrier);
	if (local_cg != 0)
	{
		local_cg->twp->counter.b[0] = pno;
		*(short *)((char *)local_8g + 6) = *(short *)((char *)local_8g + 6) & 0xfffffffc;
		*(short *)((char *)local_8g + 6) = *(short *)((char *)local_8g + 6) | 2;
	}
}

// FUNCTION: SADX 0x004f2200
void GetBarrierP(unsigned char pno)
{
	struct task *local_cg;
	struct task *local_8g;

	if (pno >= 1 && pno > 7 && DAT_05baf368[pno] == 0)
	{
		pno = 0;
	}
	local_8g = (struct task *)DAT_05ba9348[pno];
	if (local_8g == 0)
	{
		return;
	}
	if ((*(short *)((char *)local_8g + 6) & 1) != 0)
	{
		return;
	}
	local_cg = CreateElementalTask(2, 2, EffectBarrier);
	if (local_cg != 0)
	{
		local_cg->twp->counter.b[0] = pno;
		*(short *)((char *)local_8g + 6) = *(short *)((char *)local_8g + 6) & 0xfffffffc;
		*(short *)((char *)local_8g + 6) = *(short *)((char *)local_8g + 6) | 1;
	}
}

// FUNCTION: SADX 0x004f22a0
void GetInvincibleBodyP(unsigned char pno)
{
	struct task *local_cg;
	struct task *local_8g;

	if (pno >= 1 && pno > 7 && DAT_05baf368[pno] == 0)
	{
		pno = 0;
	}
	local_8g = (struct task *)DAT_05ba9348[pno];
	if (local_8g == 0)
	{
		return;
	}
	if ((*(short *)((char *)local_8g + 6) & 0x8000) != 0)
	{
		return;
	}
	local_cg = CreateElementalTask(2, 2, EffectMuteki);
	if (local_cg != 0)
	{
		local_cg->twp->counter.b[0] = pno;
		*(short *)((char *)local_8g + 6) = *(short *)((char *)local_8g + 6) | 0x8000;
		Jingle_Play(0x37);
	}
}

// FUNCTION: SADX 0x004f2340
void GetInvincibleBodyForAMomentP(unsigned char pno)
{
	struct task *local_8;

	if (pno >= 1 && pno > 7 && DAT_05baf368[pno] == 0)
	{
		pno = 0;
	}
	local_8 = CreateElementalTask(2, 0, MomentMuteki);
	if (local_8 != 0)
	{
		local_8->twp->counter.b[0] = pno;
	}
}

// STUB: SADX 0x004f23a0
static void MomentMuteki(struct task *tp)
{
}

// FUNCTION: SADX 0x004f2440
void SetHoldingItemIDP(unsigned char pno, long itemID)
{
	short *local_8;

	local_8 = (short *)DAT_05baf368[pno];
	DAT_05ba3320[*(unsigned char *)((char *)local_8 + 9)] = (char)itemID;
}

// STUB: SADX 0x004f2470
long GetHoldingItemIDP(unsigned char pno)
{
	return (long)0;
}

// FUNCTION: SADX 0x004f2530
void HoldTaskP(unsigned char pno, struct task *htp)
{
	struct taskwk *local_8;

	local_8 = DAT_05baf368[pno];
	local_8->flag = local_8->flag | 0x1000;
	local_8->smode = 0x25;
	local_8->value.ptr = htp;
}

// STUB: SADX 0x004f2570
void StopHoldingTaskP(unsigned char pno)
{
}

// FUNCTION: SADX 0x004f2610
void FUN_004f2610(void *param_1)
{
	*(void **)((char *)param_1 + 0x78) = CAlloc(0xf, 0x20);
	*(short *)((char *)param_1 + 0x12) = 0;
	return;
}

// FUNCTION: SADX 0x004f2630
void FUN_004f2630(void *param_1)
{
	if (*(void **)((char *)param_1 + 0x78) != 0)
	{
		Free(*(void **)((char *)param_1 + 0x78));
		*(void **)((char *)param_1 + 0x78) = 0;
	}
}

// FUNCTION: SADX 0x004f2660
void FUN_004f2660(int param_1)
{
	*(short *)((char *)param_1 + 0x12) = 0;
}

// STUB: SADX 0x004f2670
void EntryIslandForP(float x, float y, float z, float r)
{
}

// STUB: SADX 0x004f2dc0
void FUN_004f2dc0(struct NJS_POINT3 *arg1, struct NJS_POINT3 *arg2, struct NJS_POINT3 *arg3)
{
}

// STUB: SADX 0x004f2f70
void PPlayADXAsWaiting(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x004f31c0
void PDisableDamage(unsigned char u8Pno)
{
	int local_cg = (int)DAT_05baf368[u8Pno];
	int local_8g = DAT_05ba9348[u8Pno];
	if (local_cg == 0 || local_8g == 0)
	{
		return;
	}
	*(short *)(local_cg + 4) = *(short *)(local_cg + 4) & (short)0xfffffffb;
	*(short *)(local_cg + 6) = 1;
	*(float *)(local_8g + 0x3c) = 0.0f;
	*(float *)(local_8g + 0x38) = 0.0f;
	pdVibMxStop(0);
}

// STUB: SADX 0x004f3230
long NP_PCheckWhistle(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp, struct NP_PCHECKDATA pdatatbl)
{
	return (long)0;
}

// STUB: SADX 0x004f3350
long NP_PCheckNade(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x004f3440
void SetMovableYButtonP(unsigned char pno, long movable)
{
	DAT_05ba32e0[pno] = movable;
}

// FUNCTION: SADX 0x004f3460
long GetMovableYButtonP(unsigned char pno)
{
	return DAT_05ba32e0[pno];
}
