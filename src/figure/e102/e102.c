#include "decls.h"
extern unsigned char DAT_05cc44b8;
extern void *DAT_05cc43a4;
extern void *DAT_06276b18;
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

// STUB: SADX 0x00513900
long E102CheckJump(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00513ad0
int FUN_00513ad0(struct taskwk *param_1, int param_2, struct motionwk2 *param_3)
{
	if (DAT_05b932e8[param_1->counter.b[0]].press & jump_button)
	{
		*(float *)((char *)param_3 + 0x40) = 0.0f;
		*(float *)((char *)param_3 + 0x3c) = 0.0f;
		*(float *)((char *)param_3 + 0x38) = 0.0f;
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x005146a0
long E102CheckBeInTheAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if ((twp->flag & 3) == 0)
	{
		if ((twp->flag & 0x800) != 0)
		{
			if ((PCheckHoldObject(twp) & 0x200) != 0)
			{
				twp->mode = 0x16;
				*(short *)((char *)pwp + 0x124) = 0x21;
				return 1;
			}
			E102ThrowTheObjectOut(twp, mwp, pwp);
		}
		twp->mode = 7;
		*(short *)((char *)pwp + 0x124) = 8;
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x00514730
long E102CheckStop(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if ((unsigned short)*(unsigned short *)((char *)pwp + 0x124) == 9)
	{
		return 0;
	}
	if (PCheckPower(twp, 0, 0) == 0 && pwp->spd.x == 0.0f)
	{
		if ((twp->flag & 0x800) != 0)
		{
			if ((PCheckHoldObject(twp) & 0xc00) != 0)
			{
				twp->mode = 0x12;
				*(short *)((char *)pwp + 0x124) = 0x1e;
			}
			else
			{
				twp->mode = 0x11;
				*(short *)((char *)pwp + 0x124) = 0x19;
			}
		}
		else
		{
			FUN_005125a0(twp, mwp, pwp);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x005147e0
long FUN_005147e0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
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
					param_1->mode = 0x38;
					return 1;
				}
				break;
			}
			FUN_005125a0(param_1, param_2, param_3);
		}
	}
	return 0;
}

// FUNCTION: SADX 0x005149c0
long FUN_005149c0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	long local_8;

	PAdjustHoldingPosition(param_1, param_2, param_3);
	if (param_3->mj.nframe >= 12.0f)
	{
		local_8 = PCheckHoldObject(param_1);
		if (local_8)
		{
			switch (PCheckColliAngle(param_1, param_2))
			{
			case 4:
				if ((local_8 & 0x200) != 0)
				{
					param_1->mode = 0x11;
					if (DAT_05cc43a0 != 0)
					{
						dsPlay_oneshot(0x513, 0, 0, 0);
					}
					param_3->htp = param_1->cwp->hit_cwp->mytask;
					param_3->htp->twp->flag = param_3->htp->twp->flag | 0x1000;
					param_1->flag = param_1->flag | 0x800;
					param_1->flag = param_1->flag & ~0x8;
					return 1;
				}
				break;
			}
			FUN_005125a0(param_1, param_2, param_3);
		}
	}
	return 0;
}

// FUNCTION: SADX 0x00515140
void E102ThrowTheObjectOut(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	struct NJS_POINT3 u;
	if ((twp->flag & 0x800) != 0)
	{
		*(short *)((char *)pwp->htp->twp + 4) &= ~0x1000;
		twp->flag &= ~0x800;
		if ((PCheckHoldObject(twp) & 0x200) != 0)
		{
			u.x = 1.0f;
			u.y = 1.0f;
			u.z = 0.0f;
			njPushMatrix(&_nj_unit_matrix_);
			if (twp->ang.z != 0)
			{
				njRotateZ(0, (unsigned short)twp->ang.z);
			}
			if (twp->ang.x != 0)
			{
				njRotateX(0, (unsigned short)twp->ang.x);
			}
			if (-twp->ang.y != 0)
			{
				njRotateY(0, (unsigned short)(-twp->ang.y));
			}
			njCalcVector(0, &u, (NJS_VECTOR *)((char *)pwp->htp->mwp + 4));
			njPopMatrix(1);
		}
		pwp->htp = 0;
	}
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

// STUB: SADX 0x00515ab0
void PGetAccelerationE102_C(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
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

// FUNCTION: SADX 0x00515c90
void E102MotionCallback(struct obj *obj)
{
	if (obj == *(struct obj **)((char *)DAT_06276b18 + 0x30))
	{
		if (*(int *)((char *)DAT_05cc43a4 + 0x8c) != 0)
		{
			njRotateY(0, *(unsigned short *)((char *)DAT_05cc43a4 + 0x8c));
		}
	}
	else if (obj == *(struct obj **)((char *)DAT_06276b18 + 0x70))
	{
		FUN_0067d830(0, 0.0f, *(float *)((char *)DAT_05cc43a4 + 0x90) * 2.0f, 0.0f);
	}
}

// FUNCTION: SADX 0x00516000
int ChkTimeOverDead(struct taskwk *twp, struct playerwk *pwp)
{
	struct taskwk *local_8;

	local_8 = *(struct taskwk **)((char *)pwp + 0x7c);
	if ((char)DAT_05cc43a1 == 0)
	{
		return 0;
	}
	if (twp->mode == 0x31 || twp->mode == 0x33)
	{
		return 0;
	}
	if ((char)DAT_05cc44b8 == 0)
	{
		return 0;
	}
	if (*(char *)((char *)local_8 + 5) > 0)
	{
		return 0;
	}
	if (*(short *)((char *)local_8 + 8) < 0x3c)
	{
		return 0;
	}
	if (EV_CheckCansel() == 1)
	{
		return 0;
	}
	if (twp->id == 3)
	{
		return 0;
	}
	switch (twp->mode)
	{
		case 0x1f:
			*(short *)((char *)pwp + 0x124) = 0x46;
			break;
		case 0x21:
			*(short *)((char *)pwp + 0x124) = 0x47;
			break;
		default:
			*(short *)((char *)pwp + 0x124) = 0x45;
			break;
	}
	twp->mode = 0x31;
	KillHimP(twp->counter.b[0]);
	dsStop_id((int)twp);
	if (DAT_05cc43a0 != 0)
	{
		dsPlay_oneshot(0x5a1, 0, 0, 0);
	}
	if (local_8->mode == 3)
	{
		local_8->mode = 4;
	}
	return 1;
	return 0;
}

// STUB: SADX 0x00516140
void FUN_00516140(struct taskwk *param_1, struct E102WK *param_2, struct E102WK *param_3)
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
