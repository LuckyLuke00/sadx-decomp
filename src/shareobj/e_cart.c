#include "decls.h"
extern int DAT_04c38b98[4];
void FUN_008d0810(void);
void FUN_008d0870(void);
extern int DAT_060dff64;
extern int DAT_060dff68;
extern int DAT_060dff6c;
extern int DAT_060dff70;
void GetAngleYZV(const struct NJS_POINT3 *vec, long *ang_y, long *ang_z);
extern float _nj_unit_matrix_[16];
extern struct OBJ_CONDITION *DAT_060dfeb4;
extern int DAT_060dff60;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void FUN_008cf820(int param_1, int param_2);
void FUN_008cfbb0(int param_1, int param_2);

// FUNCTION: SADX 0x008cb900
void CartGetOffPlayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct CCL_INFO *local_8g;
	local_cg = tp->twp;
	local_8g = local_cg->cwp->info;
	DAT_060dfeb4 = (struct OBJ_CONDITION *)tp->awp->work.ptr[0];
	*(unsigned int *)((char *)local_8g + 4) &= 0xffffffef;
	GetOutOfCartP(0, 0.0, 2.0, 2.0);
	*(short *)((char *)DAT_060dfeb4 + 0x16) = 0x1e;
	returnSonicCollision(tp);
	local_cg->mode = 9;
}

// STUB: SADX 0x008cb980
void SetCartVelocity(struct task *tp, struct NJS_POINT3 *spd)
{
}

// FUNCTION: SADX 0x008cbb40
void SetCartBonusAdd(float spd)
{
	*(float *)((char *)DAT_060dfeb4 + 0x7c) = spd;
}

// STUB: SADX 0x008cbd30
void cartSnatchPlayerInfo(struct task *tp)
{
}

// STUB: SADX 0x008cccc0
void *FUN_008cccc0(void)
{
	return (void *)0;
}

// FUNCTION: SADX 0x008ccd10
void searchAnimationMaterial()
{
	if (DAT_060dff70 == 0x309)
	{
		return;
	}
	DAT_060dff64 = 0;
	reflexiveModel((struct obj *)&object_sarucart_sarucart_sarucart, 0);
	DAT_060dff68 = 0;
	reflexiveModel((struct obj *)&object_b_cart_cart_cart, 1);
	DAT_060dff6c = 0;
	reflexiveModel((struct obj *)&object_e_cart_cart_cart, 2);
	DAT_060dff70 = 0x309;
}

// FUNCTION: SADX 0x008ccd80
void reflexiveModel(struct obj *object, long scan_type)
{
	if (object->model != 0)
	{
		reflexiveMaterial(object->model, scan_type);
	}
	if (object->child != 0)
	{
		reflexiveModel(object->child, scan_type);
	}
	if (object->sibling != 0)
	{
		reflexiveModel(object->sibling, scan_type);
	}
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

// STUB: SADX 0x008d0090
void cartSetVector(struct task *tp, struct taskwk *twp)
{
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

// STUB: SADX 0x008d0500
void FUN_008d0500(float *param_1, float param_2)
{
}

// STUB: SADX 0x008d0600
void rotateFan(struct obj *obj)
{
}

// STUB: SADX 0x008d0700
void resetHoverPoint(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x008d0810
void FUN_008d0810(void)
{
	*(float *)((char *)DAT_060dfeb4 + 0x38) = *(float *)((char *)DAT_060dfeb4 + 0x38) + 1.0;
	*(float *)((char *)DAT_060dfeb4 + 0x34) = 1.0f * njSin((int)((*(float *)((char *)DAT_060dfeb4 + 0x38) * 65536.0) / 360.0)) + 0.5;
}

// FUNCTION: SADX 0x008d0870
void FUN_008d0870(void)
{
	*(float *)((char *)DAT_060dfeb4 + 0x38) = 0.0f;
	*(float *)((char *)DAT_060dfeb4 + 0x34) = *(float *)((char *)DAT_060dfeb4 + 0x34) * 0.98f;
}

// STUB: SADX 0x008d08a0
void cartRunPass(struct task *tp, struct taskwk *twp)
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

// STUB: SADX 0x008d0af0
void FUN_008d0af0(struct taskwk *param_1)
{
}

// STUB: SADX 0x008d0b60
void FUN_008d0b60(struct task *tp, int param_2)
{
}

// STUB: SADX 0x008d0ca0
long distCheck(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x008d0d20
void cartSELoop(struct task *tp, long se_no)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if ((((DAT_05b9d724 << 8) | DAT_05b9d744) & 0xff00) == 0x300)
	{
		if (distCheck(tp) != 0)
		{
			dsPlay_timer_v(*(int *)((char *)DAT_04c38b98 + se_no * 8), (int)tp, 1, 0, 2, local_8->pos.x, local_8->pos.y, local_8->pos.z);
		}
	}
	else
	{
		dsPlay_timer_v(*(int *)((char *)DAT_04c38b98 + se_no * 8 + 4), (int)tp, 1, 0, 2, local_8->pos.x, local_8->pos.y, local_8->pos.z);
	}
}

// STUB: SADX 0x008d1090
void writeSmoke(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x008d11b0
void pLockingOnTargetEnemy2(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// FUNCTION: SADX 0x008d1350
void FUN_008d1350(int param_1, char *param_2)
{
	if (DAT_060dfea8 == 1)
	{
		*param_2 = 6;
		*(char *)((char *)DAT_060dfeb4 + 0x85) = 1;
		*(char *)((char *)DAT_060dfeb4 + 0x84) = 1;
	}
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
	struct task *local_cg;
	struct taskwk *local_8g;
	if ((*(struct task *(*))&DAT_060dfeb0) == 0)
	{
		return;
	}
	local_cg = CreateElementalTask(2, 4, ego);
	local_8g = local_cg->twp;
	local_8g->pos = (*(struct task *(*))&DAT_060dfeb0)->twp->pos;
	local_8g->ang = (*(struct task *(*))&DAT_060dfeb0)->twp->ang;
	local_8g->counter.f = tp->twp->counter.f;
	local_cg->disp = drawEgo;
	tp->twp->counter.f -= 0.009999999776482582;
	if (tp->twp->counter.f <= 0.0)
	{
		tp->twp->counter.f = 0.0;
		FreeTask(tp);
		DAT_060dff60 = 0;
	}
	else
	{
		DAT_060dff60 = 1;
	}
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
