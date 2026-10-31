#include "decls.h"
extern struct NJS_ACTION action_reon2_walk2_reon2[];
void LeonWalk(struct taskwk *twp, struct enemywk *ewp);
void LeonTurnHead(struct taskwk *twp, struct enemywk *ewp);
void LeonDecideAim(struct taskwk *twp, struct enemywk *ewp);
void FUN_005c0440(struct task *param_1, struct enemywk *param_2);
void FUN_005c0a60(struct taskwk *param_1, struct enemywk *param_2);
void FUN_008d8710(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005c0b80(struct taskwk *param_1, struct enemywk *param_2);
void LeonDraw(struct taskwk *twp, struct enemywk *ewp);
void FUN_005c09e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005c0a60(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005c0b80(struct taskwk *param_1, struct enemywk *param_2);

// STUB: SADX 0x005bfe40
void EnemyLeon(struct task *tp)
{
}

// STUB: SADX 0x005c0440
void FUN_005c0440(struct task *param_1, struct enemywk *param_2)
{
}

// FUNCTION: SADX 0x005c04d0
void FUN_005c04d0(void *param_1, struct enemywk *param_2)
{
	if (((short *)param_1)[2] & 0x1000)
	{
		param_2->argb.a = param_2->argb.a - 0.017999999225139618;
		if (param_2->argb.a < -1.0)
		{
			param_2->argb.a = -1.0f;
		}
	}
	else
	{
		param_2->argb.a = param_2->argb.a + 0.012000000104308128;
		if (param_2->argb.a > 0.0)
		{
			param_2->argb.a = 0.0f;
		}
	}
}

// STUB: SADX 0x005c0560
void LeonEditMode(struct task *tp)
{
}

// FUNCTION: SADX 0x005c0950
void FUN_005c0950(struct taskwk *param_1, int param_2)
{
	CreateFlash2(param_1->pos.x, param_1->pos.y + 5.0f, param_1->pos.z, 1.4f);
	CreateExpSpring(param_1, 8);
	CreateAnimal(15, param_1->pos.x, param_1->pos.y + 15.0f, param_1->pos.z);
}

// FUNCTION: SADX 0x005c09e0
void FUN_005c09e0(struct taskwk *param_1, struct enemywk *param_2)
{
	FUN_005c0b80(param_1, param_2);
	FUN_005c0a60(param_1, param_2);
	FUN_008d8710(param_1, param_2);
	LeonDraw(param_1, param_2);
	if (EnemyDist2FromPlayer(param_1, 0) < 90000.0f)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 1;
		param_1->wtimer = 0;
	}
}

// STUB: SADX 0x005c0a60
void FUN_005c0a60(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x005c0b80
void FUN_005c0b80(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x005c0d20
void FUN_005c0d20(void *param_1, void *param_2)
{
}

// FUNCTION: SADX 0x005c1a30
void FUN_005c1a30(int param_1)
{
	float local_8;

	local_8 = *(float *)(param_1 + 0x30) - 1.0f;
	*(float *)(param_1 + 0x34) = (-*(float *)(param_1 + 0x34) * 0.2f - local_8 * 0.32f) + *(float *)(param_1 + 0x34);
	*(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x34);
	*(float *)(param_1 + 0x2c) = 2.0f - *(float *)(param_1 + 0x30);
}

// FUNCTION: SADX 0x005c1a90
void LeonWalk(struct taskwk *twp, struct enemywk *ewp)
{
	LeonDecideAim(twp, ewp);
	FUN_005c1c80(twp, ewp);
	LeonTurnHead(twp, ewp);
	FUN_005c1ca0((int)twp, (int)ewp);
	FUN_005c0a60(twp, ewp);
	FUN_008d8710(twp, ewp);
	switch (twp->smode)
	{
	case 0:
		FUN_005c0b80(twp, ewp);
		LeonDrawLink(twp, ewp);
		break;
	case 1:
		FUN_005c0b80(twp, ewp);
		if (ewp->argb.a > -0.9900000095367432)
		{
			LeonDraw(twp, ewp);
		}
		break;
	}
	if ((twp->wtimer > 0x3c) && (EnemyDist2FromAim(twp, ewp) < *(float *)((char *)ewp + 0x78) * *(float *)((char *)ewp + 0x78)))
	{
		if (((twp->flag & 0x4000) != 0) && ((twp->flag & 0x1000) != 0))
		{
			twp->flag |= 0x2000;
			twp->flag &= ~0x1000;
			EnemyCalcPlayerAngle(twp, ewp, 0);
			*(int *)((char *)twp + 0x18) = ewp->aim_angle;
		}
	}
	if (((twp->flag & 0x1000) == 0) && (ewp->argb.a > -0.10000000149011612))
	{
		ewp->old_mode = twp->mode;
		twp->mode = 2;
		twp->wtimer = 0;
		twp->btimer = 0;
		ewp->actp = (struct NJS_ACTION *)&action_reon2_walk2_reon2;
		ewp->linkactp = (struct NJS_ACTION *)&action_reon2_kihon_reon2;
		twp->smode = 0;
		twp->flag &= ~0x200;
	}
}

// STUB: SADX 0x005c1d30
void LeonTurnHead(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c2840
void LeonDecideAim(struct taskwk *twp, struct enemywk *ewp)
{
	if (EnemyCheckFrameIn((struct NJS_POINT3 *)&twp->pos))
	{
		twp->flag |= 0x4000;
	}
	else
	{
		twp->flag &= ~0x6000;
	}
	if (twp->flag & 0x2000)
	{
		ewp->aim = DAT_05baf368[0]->pos;
	}
	else
	{
		EnemyAimAroundPlayer(twp, ewp, 0, ewp->aim_num);
	}
	if (njSqrt((ewp->home.x - twp->pos.x) * (ewp->home.x - twp->pos.x) +
	          (ewp->home.y - twp->pos.y) * (ewp->home.y - twp->pos.y) +
	          (ewp->home.z - twp->pos.z) * (ewp->home.z - twp->pos.z)) > *(float *)((char *)ewp + 0x7c) + 100.0)
	{
		ewp->aim = ewp->home;
	}
}

// FUNCTION: SADX 0x005c2970
void LeonAttack(struct taskwk *twp, struct enemywk *ewp)
{
	ewp->aim = DAT_05baf368[0]->pos;
	LeonTurnHead(twp, ewp);
	FUN_008d8710(twp, ewp);
	switch (twp->smode)
	{
	case 0:
		LeonDrawLink(twp, ewp);
		break;
	case 1:
		FUN_005c0b80(twp, ewp);
		LeonDraw(twp, ewp);
		if (twp->btimer > 2 || (twp->flag & 0x200) == 0)
		{
			ewp->old_mode = twp->mode;
			twp->mode = 1;
			twp->wtimer = 0;
			twp->btimer = 0;
			ewp->linkactp = (struct NJS_ACTION *)&action_reon2_walk2_reon2;
			twp->smode = 0;
			twp->flag &= ~0x200;
			twp->flag |= 0x1000;
		}
		break;
	}
}

// STUB: SADX 0x005c2a80
void FUN_005c2a80(struct task *param_1, struct enemywk *param_2)
{
}

// FUNCTION: SADX 0x005c2b10
void CallLeonDraw(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	LeonDraw(local_cg, local_8g);
}

// FUNCTION: SADX 0x005c2b40
void CallLeonDrawLink(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	LeonDrawLink(local_cg, (struct enemywk *)local_8g);
}
