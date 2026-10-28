#include "decls.h"
long AdjustAngle(long ang0, long ang1, long dang);
long AdjustAngle(long ang0, long ang1, long dang);
extern struct CCL_INFO lift_info[3];
void AirMove(struct taskwk *twp, struct enemywk *ewp);
void AirCollision(struct taskwk *twp, struct enemywk *ewp);
void AirDraw(struct taskwk *twp, struct enemywk *ewp);
long EntryColliList(struct taskwk *twp);
long AdjustAngle(long ang0, long ang1, long dang);
extern struct obj object_sky_obj_lift_a_obj_lift_a;

// FUNCTION: SADX 0x005c2b70
void EnemyAirLift(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	CCL_Init(tp, lift_info, 3, 4);
	local_8->btimer = 0;
	local_8->wtimer = 0;
	local_8->scl.x = 0.0f;
	local_8->scl.y = -40.0f;
	local_8->ang.x = 0;
	local_8->ang.z = 0;
	tp->dest = AirLiftDestructor;
	tp->exec = AirLiftExecutor;
	tp->disp = AirLiftDraw;
	*(short *)((char *)local_8 + 4) = *(short *)((char *)local_8 + 4);
	*(short *)((char *)local_8 + 4) = *(short *)((char *)local_8 + 4) & ~0x100;
}

#pragma optimize("", off)
// STUB: SADX 0x005c2c10
void AirLiftDraw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005c2e00
void AirLiftDestructor(struct task *tp)
{
	WithdrawCollisionEntry(tp, &object_sky_obj_lift_a_obj_lift_a);
	FreeTaskC(tp);
}

// STUB: SADX 0x005c2e30
void AirLiftExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x005c2fb0
void FUN_005c2fb0(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	AirLiftDraw(param_1);
}

// STUB: SADX 0x005c2fd0
void AirLiftSleep(struct task *tp)
{
}

// STUB: SADX 0x005c3180
void EnemyAir(struct task *tp)
{
}

// STUB: SADX 0x005c3320
void AirMissle(struct task *tp)
{
}

// FUNCTION: SADX 0x005c34a0
void FUN_005c34a0(void *param_1)
{
	int local_cg;
	int local_8g;
	local_cg = *(int *)((char *)param_1 + 0x20);
	local_8g = *(int *)((char *)param_1 + 0x24);
	FUN_005b5aa0(param_1, local_cg, local_8g);
}

// FUNCTION: SADX 0x005c34d0
void MissleExecutor(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->mwp;
	if (CheckEditMode())
	{
		return;
	}
	if (CheckRangeOutWithR(tp, 4000000.0f))
	{
		return;
	}
	switch (local_cg->mode)
	{
	case 0:
		FUN_005c35b0((int)tp, (int)local_8g);
		break;
	case 1:
		MissleLockOn(tp, (struct enemywk *)local_8g);
		break;
	case 2:
		MissleAttack(tp);
		break;
	case 3:
		FUN_005c3f90(local_cg, (struct enemywk *)local_8g);
		break;
	case 4:
		FreeTask(tp);
		break;
	}
	local_cg->wtimer++;
}

// FUNCTION: SADX 0x005c35b0
void FUN_005c35b0(int param_1, int param_2)
{
	int local_cg;
	int local_8g;

	local_cg = *(int *)((char *)param_1 + 0x20);
	local_8g = *(int *)((char *)*(int *)((char *)param_1 + 8) + 0x20);
	if (*(char *)local_8g == 7)
	{
		*(char *)(param_2 + 0x49) = *(char *)local_cg;
		*(char *)local_cg = 1;
		*(short *)((char *)local_cg + 6) = 0;
	}
}

// STUB: SADX 0x005c3b30
long MissleCollision(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// STUB: SADX 0x005c3c30
void MissleDraw(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c3ee0
void FUN_005c3ee0(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x005c3f90
void FUN_005c3f90(struct taskwk *param_1, struct enemywk *param_2)
{
	MissleBombDraw(param_1, param_2);
	EntryColliList(param_1);
}

#pragma optimize("", off)
// STUB: SADX 0x005c3fc0
void MissleBombDraw(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005c40f0
void FUN_005c40f0(struct task *tp)
{
}

// STUB: SADX 0x005c42c0
void FUN_005c42c0(struct obj *param_1)
{
}

// FUNCTION: SADX 0x005c4350
void FUN_005c4350(struct task *param_1, int param_2, int param_3)
{
	FUN_005b5aa0(param_1, param_2, param_3);
	FreeTask(param_1);
}

// STUB: SADX 0x005c4380
void AirExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x005c4420
void FUN_005c4420(struct taskwk *param_1, struct enemywk *param_2)
{
	int local_8;

	local_8 = (int)param_1->cwp;
	AirCollision(param_1, param_2);
	AirDraw(param_1, param_2);
	if ((param_1->flag & 0x200) != 0)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 1;
		param_1->wtimer = 0;
		param_1->flag = (short)(param_1->flag & 0xfffffdff);
	}
	if ((param_1->flag & 0x100) != 0)
	{
		EntryColliList(param_1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x005c44b0
void AirCollision(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005c4ab0
void AirWingLightDraw(struct taskwk *twp)
{
}

// STUB: SADX 0x005c4c10
void FUN_005c4c10(struct taskwk *param_1, struct enemywk *param_2)
{
}

#pragma optimize("", off)
// STUB: SADX 0x005c4d60
void AirMove(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005c4e30
void AirRun(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c4fd0
void AirSmokeGround(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c5160
void AirTakeOff(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c5280
void FUN_005c5280(struct taskwk *param_1, struct enemywk *param_2)
{
	if (param_1->wtimer > 0x96)
	{
		*(long *)((char *)param_2 + 0x1bc) = AdjustAngle(*(long *)((char *)param_2 + 0x1bc), 0xffffd800, 0x20);
		*(long *)((char *)param_2 + 0x1b4) = AdjustAngle(*(long *)((char *)param_2 + 0x1b4), 0, 0x20);
		*(int *)((char *)param_1 + 0x18) += 0xe3;
	}
	else if (param_1->wtimer > 0x32)
	{
		*(long *)((char *)param_2 + 0x1bc) = AdjustAngle(*(long *)((char *)param_2 + 0x1bc), 0xffffd800, 0x20);
		*(long *)((char *)param_2 + 0x1b4) = AdjustAngle(*(long *)((char *)param_2 + 0x1b4), 0x800, 0x10);
		*(int *)((char *)param_1 + 0x18) += 0x88;
	}
	else
	{
		*(long *)((char *)param_2 + 0x1b4) = AdjustAngle(*(long *)((char *)param_2 + 0x1b4), 0x800, 0x20);
	}
	if (param_2->acc.x < 6.0f)
	{
		param_2->acc.x += 0.5f;
	}
	AirMove(param_1, param_2);
	AirDraw(param_1, param_2);
	if (param_1->wtimer > 0xfa)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 7;
		param_1->wtimer = 0;
	}
}

// FUNCTION: SADX 0x005c53e0
void FUN_005c53e0(struct taskwk *param_1, struct enemywk *param_2)
{
	if (param_1->wtimer > 0x96)
	{
		*(long *)((char *)param_2 + 0x1bc) = AdjustAngle(*(long *)((char *)param_2 + 0x1bc), 0x2800, 0x20);
		*(long *)((char *)param_2 + 0x1b4) = AdjustAngle(*(long *)((char *)param_2 + 0x1b4), 0, 0x10);
		*(long *)((char *)param_1 + 0x18) -= 0xe3;
	}
	else if (param_1->wtimer > 0x32)
	{
		*(long *)((char *)param_2 + 0x1bc) = AdjustAngle(*(long *)((char *)param_2 + 0x1bc), 0x2800, 0x10);
		*(long *)((char *)param_2 + 0x1b4) = AdjustAngle(*(long *)((char *)param_2 + 0x1b4), 0x800, 0x10);
		*(long *)((char *)param_1 + 0x18) -= 0x88;
	}
	else
	{
		*(long *)((char *)param_2 + 0x1b4) = AdjustAngle(*(long *)((char *)param_2 + 0x1b4), 0x800, 0x20);
	}
	if (param_2->acc.x < 6.0f)
	{
		param_2->acc.x += 0.5f;
	}
	AirMove(param_1, param_2);
	AirDraw(param_1, param_2);
	if (param_1->wtimer > 0xfa)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 7;
		param_1->wtimer = 0;
	}
}

// FUNCTION: SADX 0x005c5540
void FUN_005c5540(struct task *param_1)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;

	local_cg = param_1->twp;
	local_8g = (struct enemywk *)param_1->mwp;
	local_8g->sub_angle[1] = AdjustAngle(local_8g->sub_angle[1], 0x800, 0x20);
	if (local_8g->acc.x < 8.0)
	{
		local_8g->acc.x += 0.5;
	}
	AirMove(local_cg, local_8g);
	AirDraw(local_cg, local_8g);
}

// STUB: SADX 0x005c55d0
void FUN_005c55d0(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c5710
void AirFlyAway(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c5830
void FUN_005c5830(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	local_8->scl.x = local_8->scl.x + 0.44999998807907104;
	if (local_8->scl.x > 45.0)
	{
		local_8->scl.x = 45.0;
		local_8->mode = 2;
		local_8->wtimer = 0;
	}
	AirLiftDraw(param_1);
}

// FUNCTION: SADX 0x005c5890
void FUN_005c5890(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	*(float *)((char *)local_8 + 0x30) += 0.4f;
	if ((local_8->flag & 0x100) && param_1->ctp && (*(char *)param_1->ctp->twp != 0xc))
	{
		*(float *)((char *)param_1->ctp->twp + 0x24) += 0.4f;
	}
	if (*(float *)((char *)local_8 + 0x30) > 0.0f)
	{
		*(float *)((char *)local_8 + 0x30) = 0.0f;
		local_8->mode = 3;
		local_8->wtimer = 0;
	}
	AirLiftDraw(param_1);
}

// FUNCTION: SADX 0x005c5930
void AirLiftWait(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (local_8->wtimer > 0x3c)
	{
		local_8->mode = 4;
		local_8->wtimer = 0;
	}
	if (local_8->wtimer < 0x10)
	{
		local_8->timer.f = njSin(local_8->value.l) * 0.4f;
		local_8->value.l += 0x7500;
	}
	else
	{
		local_8->timer.f = 0.0f;
	}
	if (tp->ctp != NULL)
	{
		*(float *)((char *)tp->ctp->twp + 0x24) = *(float *)((char *)local_8 + 0x24) + 19.0f + local_8->timer.f;
	}
	if (local_8->wtimer > 5 && (local_8->flag & 0x100) != 0)
	{
		if (tp->ctp != NULL)
		{
			tp->ctp->twp->flag |= 0x200;
		}
		local_8->flag = (short)((int)local_8->flag & 0xfffffeff);
	}
	AirLiftDraw(tp);
}

// FUNCTION: SADX 0x005c5a30
void FUN_005c5a30(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	*(float *)((char *)local_8 + 0x30) -= 0.4f;
	if ((local_8->flag & 0x100) && param_1->ctp && (*(char *)param_1->ctp->twp == 0xc))
	{
		*(float *)((char *)param_1->ctp->twp + 0x24) -= 0.4f;
	}
	if (*(float *)((char *)local_8 + 0x30) < -40.0f)
	{
		*(float *)((char *)local_8 + 0x30) = -40.0f;
		local_8->mode = 5;
		local_8->wtimer = 0;
	}
	AirLiftDraw(param_1);
}

// FUNCTION: SADX 0x005c5ae0
void FUN_005c5ae0(struct task *param_1)
{
	struct taskwk *local_8 = param_1->twp;
	local_8->scl.x = local_8->scl.x - 0.44999998807907104;
	if (local_8->scl.x < 0.0)
	{
		local_8->scl.x = 0.0;
		local_8->mode = 0;
		local_8->wtimer = 0;
	}
	AirLiftDraw(param_1);
}
