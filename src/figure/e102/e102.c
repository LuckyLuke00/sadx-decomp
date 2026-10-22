#include "decls.h"
struct taskwk;
struct E102WK;
int dsPlay_oneshot(int tone, int id, int pri, int volofs);
extern char DAT_05cc43a0;
extern signed char e102_laser_enable_table[256];

// FUNCTION: SADX 0x005125a0
void FUN_005125a0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	param_1->mode = 1;
	param_3->waittimer = 0;
	E102ChangeWaitingMotion(param_1, param_2, param_3);
}

// STUB: SADX 0x005126e0
void E102Destruct(struct task *tp)
{
}

// STUB: SADX 0x00513840
int FUN_00513840(char *param_1, int param_2, int param_3)
{
	return (int)0;
}

// STUB: SADX 0x00513ad0
int FUN_00513ad0(struct taskwk *param_1, int param_2, struct motionwk2 *param_3)
{
	return (int)0;
}

// STUB: SADX 0x005146a0
long E102CheckBeInTheAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x00514730
long E102CheckStop(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x005147e0
long FUN_005147e0(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x00515550
long E102CalcHover(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x00515980
void E102ChangeRunningMotion(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x00515a50
int chkE102EnableLaser(struct taskwk *twp)
{
	return e102_laser_enable_table[twp->mode];
}

// FUNCTION: SADX 0x00515a70
void FUN_00515a70(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	PGetAcceleration(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x00515a90
void FUN_00515a90(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	PGetAccelerationAir(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x00515c30
void FUN_00515c30(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	int local_8;
	local_8 = *(int *)((char *)param_3 + 0x7c);
	PGetBreak(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x00515c60
void FUN_00515c60(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	int local_8;
	local_8 = *(int *)((char *)param_3 + 0x7c);
	PGetRotation(param_1, param_2, param_3);
}

// STUB: SADX 0x00515c90
void E102MotionCallback(struct obj *param_1)
{
}

// STUB: SADX 0x00516140
void FUN_00516140(struct taskwk *twp, struct E102WK *ewk, struct E102WK *ewk2)
{
}

// FUNCTION: SADX 0x005161d0
void SE_RDASH_ON(struct taskwk *twp, struct E102WK *ewk)
{
	if (((*(short *)((char *)ewk + 0x16) & 1) == 0))
	{
		if (DAT_05cc43a0 != 0)
		{
			dsPlay_oneshot(0x33f, 0, 0, 0);
		}
		*(short *)((char *)ewk + 0x16) = *(short *)((char *)ewk + 0x16) | 1;
	}
}

// FUNCTION: SADX 0x00516210
void SE_RDASH_OFF(struct taskwk *twp, struct E102WK *ewk)
{
	if ((*(short *)((char *)ewk + 0x16) & 1) != 0)
	{
		dsStop_num(0x33f);
		if (DAT_05cc43a0 != 0)
		{
			dsPlay_oneshot(0x33d, 0, 0, 0);
		}
		*(short *)((char *)ewk + 0x16) = *(short *)((char *)ewk + 0x16) & 0xfffffffe;
	}
}

// FUNCTION: SADX 0x00516260
long IsE102Whistling(struct taskwk *twp)
{
	if (twp->mode == 0x3a)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00516280
long IsE102ShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x1c)
	{
		return 1;
	}
	return 0;
}
