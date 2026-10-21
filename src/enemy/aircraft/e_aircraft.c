#include "decls.h"
extern double DAT_0095b120;
extern int DAT_05b9d838;
extern struct obj object_saru_air[1];
extern struct NJS_TEXLIST texlist_e_aircraft;
long AdjustAngle(long ang0, long ang1, long dang);
extern struct obj object_sky_obj_lift_a_obj_lift_a;

// STUB: SADX 0x005c2b70
void EnemyAirLift(struct task *tp)
{
}

// FUNCTION: SADX 0x005c2e00
void AirLiftDestructor(struct task *tp)
{
	WithdrawCollisionEntry(tp, &object_sky_obj_lift_a_obj_lift_a);
	FreeTaskC(tp);
}

// FUNCTION: SADX 0x005c2fb0
void FUN_005c2fb0(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	AirLiftDraw(param_1);
}

// STUB: SADX 0x005c34a0
void FUN_005c34a0(void *param_1)
{
}

// STUB: SADX 0x005c34d0
void MissleExecutor(struct task *tp)
{
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

// FUNCTION: SADX 0x005c42c0
void FUN_005c42c0(struct obj *param_1)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njSetTexture(&texlist_e_aircraft);
	njPushMatrix(0);
	njTranslateV(0, (struct NJS_POINT3 *)param_1->scl);
	if (param_1->ang[1] != 0)
	{
		njRotateY(0, param_1->ang[1]);
	}
	if (1)
	{
		njRotateY(0, 0x8000);
	}
	___dsDrawObject(&object_saru_air[0]);
	njPopMatrix(1);
}

// STUB: SADX 0x005c4350
void FUN_005c4350(struct task *tp, int param_2, int param_3)
{
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

// STUB: SADX 0x005c4d60
void AirMove(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c5540
void FUN_005c5540(struct task *param_1)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;

	local_cg = param_1->twp;
	local_8g = (struct enemywk *)param_1->mwp;
	local_8g->sub_angle[1] = AdjustAngle(local_8g->sub_angle[1], 0x800, 0x20);
	if (local_8g->acc.x < DAT_0095b120)
	{
		local_8g->acc.x += 0.5;
	}
	AirMove(local_cg, local_8g);
	AirDraw(local_cg, local_8g);
}

// STUB: SADX 0x005c5830
void FUN_005c5830(struct task *param_1)
{
}

// STUB: SADX 0x005c5890
void FUN_005c5890(struct task *tp)
{
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
