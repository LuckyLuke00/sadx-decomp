#include "decls.h"
void GetAngleYZV(const struct NJS_POINT3 *vec, long *ang_y, long *ang_z);
extern float _nj_unit_matrix_[16];
extern struct OBJ_CONDITION *DAT_060dfeb4;
extern int DAT_060dff60;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void FUN_008cf820(int param_1, int param_2);
void FUN_008cfbb0(int param_1, int param_2);

// STUB: SADX 0x008cb900
void CartGetOffPlayer(struct task *tp)
{
}

// STUB: SADX 0x008cbb40
void SetCartBonusAdd(float spd)
{
}

// STUB: SADX 0x008cbd30
void cartSnatchPlayerInfo(struct task *tp)
{
}

// STUB: SADX 0x008cd6a0
void cartShadowPos(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x008cef80
void cartSpdForceOfNature(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x008cf520
void cartTakeSonic(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x008cf620
void FUN_008cf620(struct task *tp)
{
}

// FUNCTION: SADX 0x008cf7d0
void FUN_008cf7d0(int param_1, int param_2)
{
	if ((((DAT_05b9d724 << 8) | DAT_05b9d744) & 0xff00) == 0x2300)
	{
		FUN_008cf820(param_1, param_2);
	}
	else
	{
		FUN_008cfbb0(param_1, param_2);
	}
}

// STUB: SADX 0x008d01c0
int FUN_008d01c0(struct task *param_1)
{
	return (int)0;
}

// STUB: SADX 0x008d0250
void FUN_008d0250(int param_1)
{
}

// STUB: SADX 0x008d02a0
void returnSonicCollision(struct task *tp)
{
}

// FUNCTION: SADX 0x008d0460
void calcComponentVector(struct Angle3 *ang, struct NJS_POINT3 *vec)
{
	if (njScalor(vec) == 0.0)
	{
		return;
	}
	njPushMatrix(&_nj_unit_matrix_[0]);
	if (ang->z != 0)
	{
		njRotateZ(0, (unsigned short)ang->z);
	}
	if (ang->x != 0)
	{
		njRotateX(0, (unsigned short)ang->x);
	}
	if (ang->y != 0)
	{
		njRotateY(0, (unsigned short)ang->y);
	}
	njCalcVector(0, vec, vec);
	njPopMatrix(1);
}

// STUB: SADX 0x008d0600
void rotateFan(struct obj *obj)
{
}

// STUB: SADX 0x008d0810
void FUN_008d0810(void)
{
}

// STUB: SADX 0x008d0870
void FUN_008d0870(void)
{
}

// FUNCTION: SADX 0x008d0a60
void setCartDirection(struct taskwk *twp, struct NJS_POINT3 *vec)
{
	GetAngleYZV(vec, &twp->ang.y, &twp->ang.z);
	twp->ang.x = 0;
	twp->ang.y = twp->ang.y + 0x4000;
	twp->ang.z = 0;
	*(int *)((char *)DAT_060dfeb4 + 0x24) = 0;
	if (twp->mode == 4)
	{
		if (vec->y == 0.0)
		{
			*(int *)((char *)DAT_060dfeb4 + 0x2c) = 0;
		}
		else
		{
			*(int *)((char *)DAT_060dfeb4 + 0x2c) = 0xffffeaab;
		}
	}
}

// STUB: SADX 0x008d0ca0
long distCheck(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x008d0d20
void cartSELoop(struct task *tp, long se_no)
{
}

// STUB: SADX 0x008d1350
void FUN_008d1350(int param_1, char *param_2)
{
}

// STUB: SADX 0x008d1380
void cartColliRangeChange(struct task *tp)
{
}

// FUNCTION: SADX 0x008d13d0
void MakeEgo(float rate)
{
	struct task *local_8;
	if (DAT_060dff60 == 0)
	{
		local_8 = CreateElementalTask(2, 3, egoManager);
		local_8->twp->counter.f = rate;
		DAT_060dff60 = 2;
	}
}

// STUB: SADX 0x008d1410
void egoManager(struct task *tp)
{
}

// FUNCTION: SADX 0x008d1500
void ego(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	drawEgo(tp);
	local_8->counter.f = local_8->counter.f - 0.029999999329447746;
	if (local_8->counter.f <= 0.0)
	{
		local_8->counter.f = 0.0;
		FreeTask(tp);
	}
}
