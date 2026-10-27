#include "decls.h"
extern struct PDS_PERIPHERAL DAT_05b932e8[8];
extern long action_button;
extern int DAT_060eea5c;
struct playerwk;
void FUN_00547070(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
extern short DAT_05b9d724;
void FUN_004e2f70(int param_1, int param_2);
int FUN_0054f7b0(struct playerwk *param_1, int param_2);
extern int sonic_snowboard_design;
extern struct NJS_TEXLIST texlist_s_sboard;
extern struct NJS_TEXLIST texlist_sb[2];
void FUN_0054f850(struct playerwk *param_1);
extern void *DAT_060eea60;
extern void *DAT_06276b1c;
void FUN_0054f960(struct task *param_1);
int FUN_0054f7b0(struct playerwk *param_1, int param_2);
extern unsigned char DAT_05bb00a9;
int FUN_0054f7b0(struct playerwk *param_1, unsigned short param_2);
int FUN_0054f920(int param_1);
extern struct taskwk *DAT_05baf368[8];

// FUNCTION: SADX 0x00547070
void FUN_00547070(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	param_1->mode = 1;
	param_3->waittimer = 0;
	SonicChangeWaitingMotion(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x005471b0
void SonicDestruct(struct task *tp)
{
	struct taskwk *local_10;
	struct motionwk2 *local_8g;
	struct playerwk *local_cj;
	local_10 = tp->twp;
	local_8g = (struct motionwk2 *)tp->mwp;
	local_cj = (struct playerwk *)local_8g->work.ptr;
	*(unsigned short *)((char *)local_cj + 0x124) = 0;
	SonicInterpolateFeetModel(local_10, local_8g, local_cj);
	PDestruct(local_10->counter.b[0]);
	dsStop_id((int)local_10);
	if (DAT_05bb00a9 != 0)
	{
		ReleasePlayersTexture(8);
	}
	ReleasePlayersTexture(0);
}

// STUB: SADX 0x00547230
void FUN_00547230(struct task *tp, int param_2, int param_3)
{
}

// STUB: SADX 0x005478e0
void SonicChangeRunningMotion(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x00547a80
void FUN_00547a80(struct task *param_1, struct task *param_2, struct taskwk *param_3)
{
}

// FUNCTION: SADX 0x005488e0
void FUN_005488e0(char *param_1, char *param_2, char *param_3)
{
	if (*(float *)(param_3 + 0x38) < *(float *)(param_3 + 0xc0))
		return;
	int local_8;
	if ((((DAT_05b9d724 << 8) | DAT_05b9d744) & 0xff00) == 0x800)
	{
		if (*(int *)(param_3 + 0x5c) == 4)
		{
			local_8 = 0xe1;
		}
		else if (*(int *)(param_3 + 0x5c) == 8)
		{
			local_8 = 0xe3;
		}
		else
		{
			local_8 = 0xe2;
		}
	}
	else
	{
		local_8 = 0x2d9;
	}
	PSetLoopSECallForTheMode((long)local_8, (unsigned char)param_1[8], (short)(signed char)*param_1);
}

// STUB: SADX 0x00548980
void FUN_00548980(struct taskwk *twp)
{
}

// STUB: SADX 0x00548b90
void SonicHomeOnTarget(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x00549ed0
long SonicCheckJumpCancel(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if (DAT_05b932e8[twp->counter.b[0]].press & action_button)
	{
		twp->mode = 0xc;
		FUN_004e2f70(0, (int)pwp);
		*(short *)((char *)pwp + 0x124) = 0x12;
		pwp->work.f = 0.0f;
		twp->flag &= ~0x500;
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x0054bdd0
long SonicCheckInputInSnowBoard(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if ((twp->flag & 0x1000) == 0)
	{
		return 0;
	}
	if (twp->smode == 0x18)
	{
		twp->mode = 0xc;
		*(unsigned short *)((char *)pwp + 0x124) = 0x12;
		return 1;
	}
	else if (twp->smode == 0x13)
	{
		SonicThrowTheObjectOut(twp, mwp, pwp);
		twp->mode = 0x14;
		*(unsigned short *)((char *)pwp + 0x124) = 0x4b;
		*(int *)((char *)twp + 0x1c) = 0;
		*(int *)((char *)twp + 0x14) = 0;
		FUN_004e2f70((int)mwp, (int)pwp);
		twp->flag = twp->flag & ~0x2000;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0054c330
long SonicCheckBeInTheAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if (((twp->flag & 3) == 0))
	{
		if ((twp->flag & 0x100) != 0)
		{
			twp->mode = 8;
			return 1;
		}
		else if ((0x800 & twp->flag) != 0)
		{
			if ((PCheckHoldObject(twp) & 0x200) != 0)
			{
				twp->mode = 0x1c;
				*(unsigned short *)((char *)pwp + 0x124) = 0x39;
				return 1;
			}
			SonicThrowTheObjectOut(twp, mwp, pwp);
		}
		twp->mode = 0xc;
		*(unsigned short *)((char *)pwp + 0x124) = 0x12;
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x0054c3e0
long SonicCheckStop(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if ((PCheckPower(twp, 0, 0) == 0) && (pwp->spd.x == 0.0f))
	{
		if ((twp->flag & 0x800) != 0)
		{
			if ((PCheckHoldObject(twp) & 0xc00) != 0)
			{
				twp->mode = 0x18;
				*(short *)((char *)pwp + 0x124) = 0x36;
			}
			else
			{
				twp->mode = 0x17;
				*(short *)((char *)pwp + 0x124) = 0x25;
			}
		}
		else
		{
			FUN_00547070(twp, mwp, pwp);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x0054c480
long SonicCheckStartSpin(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if (DAT_05b932e8[twp->counter.b[0]].press & action_button)
	{
		twp->mode = 4;
		ChangeMotionSonicSpin(pwp);
		twp->flag |= 0x500;
		*(short *)((char *)pwp + 0x7e) = 0;
		if (pwp->spd.x > 2.0)
		{
			pwp->work.f = pwp->spd.x;
		}
		else
		{
			pwp->work.f = 2.0f;
		}
		dsPlay_timer(0x2ff, (int)twp, 1, 0, 2);
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x0054c520
long SonicCheckStartLSDorLSA(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0054c9d0
int FUN_0054c9d0(unsigned char *param_1, int param_2, int param_3)
{
	return (int)0;
}

// FUNCTION: SADX 0x0054ca40
long FUN_0054ca40(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	long local_8;

	PAdjustHoldingPosition(param_1, param_2, param_3);
	if (param_3->mj.nframe >= 6.0f)
	{
		local_8 = PCheckHoldObject(param_1);
		if (local_8)
		{
			switch (PCheckColliAngle(param_1, param_2))
			{
			case 4:
				if ((local_8 & 0x200) != 0)
				{
					param_1->mode = 0x48;
					return 1;
				}
				break;
			}
			FUN_00547070(param_1, param_2, param_3);
		}
	}
	return 0;
}

// STUB: SADX 0x0054cae0
long SonicCheckHoldObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0054cc20
long SonicCheckPickObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0054cd40
long SonicCheckThrowObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0054d2d0
long SonicCheckTouch(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

#pragma optimize("", off)
// STUB: SADX 0x0054d450
void SonicThrowTheObjectOut(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0054d870
void SonicHoldOnPillar(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	int local_8g;
	int local_cj;
	float local_10;

	local_cj = *(int *)((char *)pwp->htp + 0x20);
	local_8g = *(int *)((char *)pwp->htp + 0x24);
	if (local_8g == 0)
	{
		local_10 = 30.0f;
	}
	else
	{
		local_10 = *(float *)((char *)local_8g + 0x34);
	}
	twp->pos.x = *(float *)((char *)local_cj + 0x20) - njCos(*(long *)((char *)twp + 0x18)) * local_10;
	twp->pos.z = *(float *)((char *)local_cj + 0x28) - njSin(*(long *)((char *)twp + 0x18)) * local_10;
}

// STUB: SADX 0x0054d9e0
void SonicHoldOnIcicle(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x0054dce0
void SonicFaceMotion(struct task *tp)
{
	struct motionwk *local_8;

	local_8 = (struct motionwk *)CAlloc(1, 0x20);
	if (local_8 == 0)
	{
		return;
	}
	tp->mwp = local_8;
	*(long *)((char *)local_8 + 0x10) = *(long *)((char *)DAT_060eea60 + 0xb4);
	*(long *)((char *)local_8 + 0x14) = *(long *)((char *)DAT_060eea60 + 0xb8);
	*(long *)((char *)local_8 + 0x18) = *(long *)((char *)DAT_060eea60 + 0xbc);
	*(long *)((char *)local_8 + 0x1c) = *(long *)DAT_06276b1c;
	tp->dest = PlayerFaceMotionEnd;
	tp->exec = PlayerFaceMotionExec;
}

// STUB: SADX 0x0054e460
void SonicHeadSpikesShakeEnd(struct task *tp)
{
}

// STUB: SADX 0x0054e480
int FUN_0054e480(char param_1, float *param_2)
{
	return (int)0;
}

// FUNCTION: SADX 0x0054ea70
void PSetDashEffect(struct taskwk *twp)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 6, EffectDash);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)twp + 8);
	}
}

// FUNCTION: SADX 0x0054eab0
void FUN_0054eab0(struct taskwk *param_1)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 6, EffectSSDash);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)param_1 + 8);
	}
}

// FUNCTION: SADX 0x0054eaf0
void FUN_0054eaf0(struct taskwk *param_1)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 5, EffectSpin);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)param_1 + 8);
	}
}

// FUNCTION: SADX 0x0054eb30
void PSetSpinDSEffect(struct taskwk *twp)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 5, EffectSpinDS);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)twp + 8);
	}
}

// FUNCTION: SADX 0x0054eb70
void FUN_0054eb70(struct taskwk *param_1)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 5, EffectSSSpinDS);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)param_1 + 8);
	}
}

// FUNCTION: SADX 0x0054ebb0
void FUN_0054ebb0(struct taskwk *param_1)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 5, EffectStartHoming);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)param_1 + 8);
	}
}

// FUNCTION: SADX 0x0054ebf0
void FUN_0054ebf0(struct taskwk *param_1)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 5, EffectSSStartHoming);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 8) = *(unsigned char *)((char *)param_1 + 8);
	}
}

// FUNCTION: SADX 0x0054ec30
void FUN_0054ec30(struct taskwk *param_1, int param_2, struct taskwk *param_3)
{
	struct task *local_8;
	local_8 = CreateElementalTask(8, 0, ManageSonicLightSpinCharge);
	if (local_8)
	{
		*(struct taskwk **)(local_8->awp) = param_1;
		*(int *)((char *)local_8->awp + 4) = (int)param_3;
		*(float *)((char *)local_8->awp + 8) = *(float *)((char *)param_3 + 0xac);
		*(float *)((char *)param_3 + 0xac) = 0.5f;
		local_8->dest = ManageSonicLightSpinChargeExit;
	}
}

// STUB: SADX 0x0054eca0
void ManageSonicLightSpinCharge(struct task *tp)
{
}

// FUNCTION: SADX 0x0054ed00
void ManageSonicLightSpinChargeExit(struct task *tp)
{
	struct OBJ_EDITENTRY *local_8;
	local_8 = *(struct OBJ_EDITENTRY **)((char *)tp->awp + 4);
	if (DAT_05baf368[0] != 0)
	{
		*(float *)((char *)local_8 + 0xac) = *(float *)((char *)tp->awp + 8);
	}
}

// FUNCTION: SADX 0x0054ed30
void SonicSnowBoard(struct task *tp)
{
	struct taskwk *local_8g;
	int local_cg;

	local_8g = tp->twp;
	local_8g->timer.ptr = *(void **)((char *)DAT_060eea60 + 0x11c);
	local_cg = (int)(GetGlobalTime() % (unsigned long)(sonic_snowboard_design + 1));
	if (local_cg >= sonic_snowboard_design)
	{
		local_8g->value.ptr = &texlist_s_sboard;
	}
	else
	{
		local_8g->value.ptr = &texlist_sb[local_cg];
	}
	tp->mwp->weight = 0.019999999552965164f;
	NeonuLoadTexture((struct NJS_TEXLIST *)local_8g->value.ptr);
	tp->dest = DstrReleaseTexture;
	tp->exec = ExecuteSonicSnowBoard;
	tp->disp = DisplaySonicSnowBoard;
}

#pragma optimize("", off)
// STUB: SADX 0x0054edd0
void ExecuteSonicSnowBoard(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0054f150
void SuperSonicStatusManager(struct task *tp)
{
	struct anywk *local_10;
	struct playerwk *local_8g;
	unsigned char local_9;
	local_10 = tp->awp;
	local_9 = *(unsigned char *)local_10;
	local_8g = GetPlayerWorkPointer(local_9);
	if (local_8g == 0)
	{
		DestroyTask(tp);
	}
	else
	{
		*(float *)((char *)local_10 + 4) = *(float *)((char *)local_8g + 0xf0);
		*(float *)((char *)local_10 + 8) = *(float *)((char *)local_8g + 0xec);
		*(float *)((char *)local_10 + 0xc) = *(float *)((char *)local_8g + 0xdc);
		*(float *)((char *)local_8g + 0xf0) = -0.001f;
		*(float *)((char *)local_8g + 0xec) = -0.002f;
		*(float *)((char *)local_8g + 0xdc) = 0.05f;
		*(float *)((char *)local_8g + 0x11c) = 6.4f;
		tp->dest = SuperSonicStatusManagerDestructor;
		tp->exec = SuperSonicStatusManagerExecutor;
	}
}

// FUNCTION: SADX 0x0054f210
void SuperSonicStatusManagerDestructor(struct task *tp)
{
	struct anywk *local_10;
	unsigned char local_9;
	struct playerwk *local_8g;
	local_10 = tp->awp;
	local_9 = *(unsigned char *)local_10;
	local_8g = GetPlayerWorkPointer(local_9);
	if (local_8g == 0)
		return;
	*(float *)((char *)local_8g + 0xac) = local_10->work.f[1];
	*(float *)((char *)local_8g + 0xd8) = local_10->work.f[2];
	*(float *)((char *)local_8g + 0xdc) = local_10->work.f[3];
	*(float *)((char *)local_8g + 0x11c) = 5.4f;
}

// FUNCTION: SADX 0x0054f280
void SuperSonicStatusManagerExecutor(struct task *tp)
{
	struct anywk *local_10;
	struct playerwk *local_8g;
	unsigned char local_9;
	local_10 = tp->awp;
	local_9 = *(unsigned char *)local_10;
	local_8g = GetPlayerWorkPointer(local_9);
	if (local_8g == 0)
	{
		DestroyTask(tp);
	}
	else if ((local_8g->equipment & 0x8000) == 0)
	{
		DestroyTask(tp);
	}
}

// FUNCTION: SADX 0x0054f2e0
void SonicCanselSpinDashForIcecap(struct taskwk *twp, struct playerwk *pwp)
{
	if ((twp->flag & 0x100) != 0)
	{
		twp->mode = 2;
		*(unsigned short *)((char *)pwp + 0x124) = 0x1d;
		twp->flag &= 0xfffffaff;
	}
}

// STUB: SADX 0x0054f570
void DrawSonicMotionLink(struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x0054f760
void ChangeMotionSonicRush(struct playerwk *pwp)
{
	if (DAT_05bb00a9 != 0)
	{
		if (FUN_0054f7b0(pwp, 0x92) == 0)
		{
			FUN_0054f920(5);
		}
		*(short *)((char *)pwp + 0x124) = 0x92;
	}
	else
	{
		*(short *)((char *)pwp + 0x124) = 0xc;
	}
}

// FUNCTION: SADX 0x0054f7b0
int FUN_0054f7b0(struct playerwk *param_1, int param_2)
{
	if (*(unsigned short *)((char *)param_1 + 0x124) == param_2)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x0054f7d0
void ChangeMotionSonicLaunch(struct playerwk *pwp)
{
	if (DAT_05bb00a9 != 0)
	{
		if (FUN_0054f7b0(pwp, 0x10) == 0)
		{
			FUN_0054f920(0x14);
		}
	}
	*(short *)((char *)pwp + 0x124) = 0x10;
}

// FUNCTION: SADX 0x0054f810
void ChangeMotionSonicRun(struct playerwk *pwp)
{
	if (DAT_05bb00a9 != 0)
	{
		if (FUN_0054f7b0(pwp, 0x92) != 0)
		{
			FUN_0054f920(5);
		}
	}
	*(short *)((char *)pwp + 0x124) = 0xb;
}

// FUNCTION: SADX 0x0054f850
void FUN_0054f850(struct playerwk *param_1)
{
	if (DAT_05bb00a9 != 0)
	{
		if (FUN_0054f7b0(param_1, 0xd) == 0)
		{
			FUN_0054f920(0xa);
		}
	}
	param_1->mj.reqaction = 0xd;
}

// FUNCTION: SADX 0x0054f890
void ChangeMotionSonicSpin(struct playerwk *pwp)
{
	if (DAT_05bb00a9 != 0)
	{
		if (FUN_0054f7b0(pwp, 0xe) == 0)
		{
			FUN_0054f920(0xa);
		}
	}
	*(short *)((char *)pwp + 0x124) = 0xe;
}

// STUB: SADX 0x0054f8d0
long CreateBlurManagerForMetalSonic(long timer)
{
	return (long)0;
}

// FUNCTION: SADX 0x0054f910
void FUN_0054f910()
{
	FUN_004f5550(0x59);
}

// FUNCTION: SADX 0x0054f920
int FUN_0054f920(int param_1)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 3, FUN_0054f960);
	if (local_8 == 0)
	{
		return 0;
	}
	*(int *)((char *)local_8->twp + 0xc) = param_1;
	return 1;
}

// STUB: SADX 0x0054f960
void FUN_0054f960(struct task *param_1)
{
}

// FUNCTION: SADX 0x0054fa60
void FUN_0054fa60(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	DrawBlurOfMetalSonic(param_1);
	local_8->counter.f -= 0.1f;
	if (local_8->counter.f <= 0.0f)
	{
		FreeTask(param_1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0054fab0
void DrawBlurOfMetalSonic(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0054fc20
long IsSonicWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x4a)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x0054fc80
void _sonicmot_init()
{
	DAT_05cc7fe8 = *(int *)((char *)DAT_060eea5c + 0x190);
	DAT_05cc7ff8 = *(int *)((char *)DAT_060eea5c + 0x194);
}
