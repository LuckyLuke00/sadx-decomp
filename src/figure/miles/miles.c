#include "decls.h"
extern long action_button;
void FUN_0053e4f0(struct taskwk *param_1, int param_2, int param_3);
struct task;
extern struct NJS_TEXLIST texlist_m_sboard_snowboard;
extern void *DAT_06298ce8;
extern void *DAT_06298ccc;
extern void *DAT_06276c34;
void FUN_0053ba40(void);
extern int DAT_05b3e05c;
extern unsigned char DAT_05cd14e1;
void FUN_00554ca0(int param_1);
void FUN_0053e5c0(struct task *param_1);

// FUNCTION: SADX 0x005360c0
long Board_AddScore(long score)
{
	if (DAT_05b3e05c == 9 && DAT_05cd14e1 == 1)
	{
		FUN_00554ca0((int)score);
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x005360f0
void FUN_005360f0(struct taskwk *param_1, struct playerwk *param_2)
{
	param_1->mode = 1;
	param_2->waittimer = 0;
	MilesChangeWaitingMotion(param_1, param_2);
}

// FUNCTION: SADX 0x00536230
void MilesDestruct(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	FUN_0053ba40();
	PDestruct(local_8->counter.b[0]);
	dsStop_id((int)local_8);
	ReleasePlayersTexture(2);
}

// STUB: SADX 0x00536270
void FUN_00536270(struct task *param_1, void *param_2)
{
}

// STUB: SADX 0x005370b0
float GetUnitVector(struct NJS_POINT3 *vec)
{
	return (float)0;
}

// STUB: SADX 0x00537180
void MilesChangeRunningMotion(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x00538070
void MilesSBoardSlideSECall(struct taskwk *twp, struct playerwk *pwp)
{
}

// STUB: SADX 0x00538110
long MilesCheckDamage(struct taskwk *twp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00538480
int FUN_00538480(void *param_1, void *param_2)
{
	if (DAT_05b932e8[*(unsigned char *)((char *)param_1 + 8)].press & action_button)
	{
		*(char *)param_1 = 0xa;
		FUN_004e2f70(0, (int)param_2);
		*(short *)((char *)param_2 + 0x124) = 0x13;
		*(float *)param_2 = 0.0f;
		*(short *)((char *)param_1 + 4) &= ~0x500;
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x005394e0
long MilesCheckAutoPilot(struct taskwk *param_1, ...)
{
	return (long)0;
}

// STUB: SADX 0x0053a070
long MilesCheckInputInSnowBoard(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0053a180
long MilesCheckBeInTheAir(struct taskwk *twp, struct playerwk *pwp)
{
	if (((twp->flag & 3) == 0))
	{
		if ((twp->flag & 0x100) != 0)
		{
			twp->mode = 6;
			return 1;
		}
		else if ((0x800 & twp->flag) != 0)
		{
			if ((PCheckHoldObject(twp) & 0x200) != 0)
			{
				twp->mode = 0x1c;
				*(unsigned short *)((char *)pwp + 0x124) = 0x52;
				return 1;
			}
			MilesThrowTheObjectOut(twp, pwp);
		}
		twp->mode = 0xa;
		*(unsigned short *)((char *)pwp + 0x124) = 0x13;
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x0053a220
long FUN_0053a220(struct taskwk *param_1, struct playerwk *param_2)
{
	if (PCheckPower(param_1, 0, 0) == 0 && param_2->spd.x == 0.0f)
	{
		if ((param_1->flag & 0x800) != 0)
		{
			if ((PCheckHoldObject(param_1) & 0xc00) != 0)
			{
				param_1->mode = 0x18;
				*(short *)((char *)param_2 + 0x124) = 0x4f;
			}
			else
			{
				param_1->mode = 0x17;
				*(short *)((char *)param_2 + 0x124) = 0x3e;
			}
		}
		else
		{
			FUN_005360f0(param_1, param_2);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x0053a2c0
int FUN_0053a2c0(char *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0053a330
long MilesCheckHoldObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0053a470
long MilesCheckPickObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0053ac60
void MilesThrowTheObjectOut(struct taskwk *twp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x0053b090
void MilesHoldOnPillar(struct taskwk *twp, struct playerwk *pwp)
{
	int local_ci;
	int local_8g;
	float local_10;

	local_ci = *(int *)((char *)pwp->htp + 0x20);
	local_8g = *(int *)((char *)pwp->htp + 0x24);
	if (local_ci == 0)
	{
		twp->mode = 1;
	}
	else
	{
		if (local_8g == 0)
		{
			local_10 = 30.0f;
		}
		else
		{
			local_10 = *(float *)((char *)local_8g + 0x34);
		}
		twp->pos.x = *(float *)((char *)local_ci + 0x20) - njCos(*(long *)((char *)twp + 0x18)) * local_10;
		twp->pos.z = *(float *)((char *)local_ci + 0x28) - njSin(*(long *)((char *)twp + 0x18)) * local_10;
	}
}

// STUB: SADX 0x0053b120
int FUN_0053b120(struct task *param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x0053b210
long MilesCheckStop(struct taskwk *twp, struct playerwk *pwp)
{
	if (DAT_05b932e8[twp->counter.b[0]].press & action_button)
	{
		twp->mode = 4;
		*(short *)((char *)pwp + 0x124) = 0xf;
		twp->flag |= 0x500;
		pwp->work.f = pwp->spd.x;
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x0053b270
long MilesCheckStartTAttack(struct taskwk *twp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0053b850
void MilesReformTailDependOnX()
{
}

// FUNCTION: SADX 0x0053ba40
void FUN_0053ba40(void)
{
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x38) + 0x14) = 0;
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x3c) + 0x14) = 0;
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x30) + 4) = *(int *)((char *)DAT_06276c34 + 0x14);
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x34) + 4) = *(int *)((char *)DAT_06276c34 + 0x18);
}

// STUB: SADX 0x0053be50
int FUN_0053be50(char param_1, struct NJS_POINT3 *param_2)
{
	return (int)0;
}

// STUB: SADX 0x0053bee0
int FUN_0053bee0(unsigned char param_1, struct NJS_POINT3 *param_2)
{
	return (int)0;
}

// STUB: SADX 0x0053cb70
void MilesStareAt(struct pheadeyewk *phewp)
{
}

// STUB: SADX 0x0053ddc0
void MilesHeadSpikesShakeEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x0053ddf0
void MilesFaceMotion(struct task *tp)
{
	struct motionwk *local_8;

	local_8 = (struct motionwk *)CAlloc(1, 0x20);
	if (local_8 == 0)
	{
		return;
	}
	tp->mwp = local_8;
	*(long *)((char *)local_8 + 0x18) = *(long *)((char *)DAT_06298ccc + 0x118);
	*(long *)((char *)local_8 + 0x1c) = *(long *)DAT_06298ce8;
	tp->dest = PlayerFaceMotionEnd;
	tp->exec = MilesFaceMotionExec;
}

// STUB: SADX 0x0053de50
void MilesFaceMotionExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0053df40
void MilesSnowBoard(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	local_8->timer.ptr = *(void **)((char *)DAT_06298ccc + 0x11c);
	local_8->value.ptr = &texlist_m_sboard_snowboard;
	tp->mwp->weight = 0.019999999552965164f;
	NeonuLoadTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	tp->dest = DstrReleaseTexture;
	tp->exec = ExecuteMilesSnowBoard;
	tp->disp = DisplayMilesSnowBoard;
}

// STUB: SADX 0x0053dfb0
void ExecuteMilesSnowBoard(struct task *tp)
{
}

// STUB: SADX 0x0053e320
void SetMilesFinishAction()
{
}

// FUNCTION: SADX 0x0053e4f0
void FUN_0053e4f0(struct taskwk *param_1, int param_2, int param_3)
{
	if (*(unsigned char *)((char *)param_1 + 8) == 1)
		return;
	dsPlay_oneshot(param_2, 0, param_3, 0);
}

// FUNCTION: SADX 0x0053e520
void FUN_0053e520(struct taskwk *param_1)
{
	if (!(1 != param_1->counter.b[0] && PCheckHoldObject(param_1) & 0x400))
		return;
	dsPlay_timer(0xf, (int)param_1, 1, 0, 2);
}

// FUNCTION: SADX 0x0053e560
void FUN_0053e560(struct taskwk *param_1)
{
	if (*(unsigned char *)((char *)param_1 + 8) == 1)
		return;
	dsStop_num(0xf);
}

// FUNCTION: SADX 0x0053e580
void MilesSEControle(struct task *tp)
{
	struct task *local_8;
	local_8 = CreateElementalTask(8, 1, FUN_0053e5c0);
	if (local_8)
	{
		local_8->awp->work.ul[0] = 6;
		local_8->awp->work.ul[1] = (long)tp;
	}
}

// FUNCTION: SADX 0x0053e5c0
void FUN_0053e5c0(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	local_8->work.sl[0] = local_8->work.sl[0] - 1;
	if (local_8->work.sl[0] <= 0)
	{
		Serif_Play(local_8->work.sl[1]);
		DestroyTask(param_1);
	}
}

// FUNCTION: SADX 0x0053e610
long IsTailsWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x42)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x0054fc40
long IsTailsPutting(struct taskwk *twp)
{
	if (twp->mode == 0x16)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x0054fc60
long IsTailsShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x22)
		return 1;
	return 0;
}
