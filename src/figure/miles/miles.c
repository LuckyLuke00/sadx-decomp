#include "decls.h"
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

// STUB: SADX 0x00538480
int FUN_00538480(void *param_1, void *param_2)
{
	return (int)0;
}

// STUB: SADX 0x0053a2c0
int FUN_0053a2c0(char *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0053b210
long MilesCheckStop(struct taskwk *twp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0053ba40
void FUN_0053ba40(void)
{
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x38) + 0x14) = 0;
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x3c) + 0x14) = 0;
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x30) + 4) = *(int *)((char *)DAT_06276c34 + 0x14);
	*(int *)((char *)*(void **)((char *)DAT_06298ccc + 0x34) + 4) = *(int *)((char *)DAT_06276c34 + 0x18);
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

// FUNCTION: SADX 0x0053e4f0
void FUN_0053e4f0(struct taskwk *param_1, int param_2, int param_3)
{
	if (*(unsigned char *)((char *)param_1 + 8) == 1)
		return;
	dsPlay_oneshot(param_2, 0, param_3, 0);
}

// STUB: SADX 0x0053e520
void FUN_0053e520(struct taskwk *twp)
{
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
