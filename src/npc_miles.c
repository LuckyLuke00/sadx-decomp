#include "decls.h"
extern int DAT_05cd14f4;
extern "C" double atan2(double v, double u);
void SetInputP(unsigned char pno, signed char mode);
extern int DAT_05cd14f8;
void EV_NpcMilesStandByOff();

// STUB: SADX 0x005ac960
struct task *NpcMilesSet(struct task *tp1p)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x005aca60
void NpcMilesControlDestructor(struct task *tp)
{
	DAT_05cd14f8 = 0;
	EV_NpcMilesStandByOff();
}

// FUNCTION: SADX 0x005aca80
int FUN_005aca80(void)
{
	int local_8;
	local_8 = DAT_05cd14f8;
	if (local_8 == 0)
	{
		return 0;
	}
	*(char *)*(int **)((char *)local_8 + 0x20) = 0;
	return 1;
}

// STUB: SADX 0x005acab0
long ComeBackNpcMiles()
{
	return (long)0;
}

// STUB: SADX 0x005acaf0
long FreeNpcMilesPlayerTask()
{
	return (long)0;
}

// FUNCTION: SADX 0x005acb60
struct task *CreateNpcMilesPlayerTask()
{
	struct task *local_8;
	if (DAT_05cd14f8 == 0)
	{
		return 0;
	}
	local_8 = CreateElementalTask(7, 1, MilesTalesPrower);
	if (local_8 != 0)
	{
		*(unsigned char *)((char *)local_8->twp + 9) = 2;
		*(unsigned char *)((char *)local_8->twp + 8) = 1;
	}
	return local_8;
}

// FUNCTION: SADX 0x005ad150
void SetPlayerFlyMode(unsigned char plno)
{
	struct csts *local_8g;
	struct playerwk *local_cg;

	local_8g = (struct csts *)DAT_05ba3328[plno];
	local_cg = GetPlayerWorkPointer(plno);
	if ((local_8g != 0) && (local_cg != 0))
	{
		local_8g->pos.z = 0.0f;
		local_8g->pos.y = 0.0f;
		local_8g->pos.x = 0.0f;
		local_cg->spd.z = 0.0f;
		local_cg->spd.y = 0.0f;
		local_cg->spd.x = 0.0f;
		SetInputP(plno, 0x30);
	}
}

// FUNCTION: SADX 0x005ad7f0
float FUN_005ad7f0(float *param_1)
{
	return njSqrt(param_1[0] * param_1[0] + param_1[1] * param_1[1] + param_1[2] * param_1[2]);
}

// FUNCTION: SADX 0x005ad830
float FUN_005ad830(float *param_1, float *param_2)
{
	float local_ci;
	float local_10;
	float local_8g;

	local_10 = param_2[0] - param_1[0];
	local_8g = param_2[1] - param_1[1];
	local_ci = param_2[2] - param_1[2];
	local_10 = local_10 * local_10 + local_8g * local_8g + local_ci * local_ci;
	return njSqrt(local_10);
}

// STUB: SADX 0x005ad890
void FUN_005ad890(struct task *param_1, float *param_2, float *param_3)
{
}

// FUNCTION: SADX 0x005ada20
void GetPlayerSidePos(struct taskwk *twp, float dist, struct NJS_POINT3 *pos)
{
	float local_8g;
	float local_cg;

	if ((twp != 0) && (pos != 0))
	{
		local_8g = njSin(*(int *)((char *)twp + 0x18));
		local_cg = njCos(*(int *)((char *)twp + 0x18));
		pos->x = twp->pos.x - dist * local_cg;
		pos->y = twp->pos.y;
		pos->z = twp->pos.z - dist * local_8g;
	}
}

// STUB: SADX 0x005ada90
long NpcGetAngleToTarget(struct NJS_POINT3 *ps, struct NJS_POINT3 *pd, float *dist, float *distxz)
{
	return (long)0;
}

// FUNCTION: SADX 0x005adb60
void NpcGetAnalogForBrake(struct NJS_POINT3 *spd, float *stroke, long *angle)
{
	if ((spd->x == 0.0f) && (spd->z == 0.0f))
	{
		if (stroke != 0)
		{
			*stroke = 0.0f;
		}
		if (angle != 0)
		{
			*angle = 0;
		}
	}
	else
	{
		if (stroke != 0)
		{
			*stroke = 1.0f;
		}
		if (angle != 0)
		{
			*angle = (long)(atan2(spd->z, spd->x) * 65536.0 / 6.283184) + 0x8000;
		}
	}
}

// FUNCTION: SADX 0x005adc00
long NpcCheckBothDamage(struct task *tp1, struct task *tp2)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;

	local_cg = tp1->twp;
	local_8g = tp2->twp;
	if ((tp1 == 0) || (tp2 == 0))
	{
		return 0;
	}
	if (((local_cg->flag & 0x408) == 0x408))
	{
		if (((local_cg->cwp->hit_cwp->mytask) == tp2) && ((local_8g->flag & 0x400) != 0))
		{
			return 1;
		}
	}
	else
	{
		if (((local_8g->flag & 0x408) == 0x408) && ((local_8g->cwp->hit_cwp->mytask) == tp1) && ((local_cg->flag & 0x400) != 0))
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x005adf30
int FUN_005adf30()
{
	if (DAT_05cd14ea == 1)
	{
		return 1;
	}
	if (SeqCheckFlag(0x48))
	{
		return 1;
	}
	if (EV_CheckExec(0x100))
	{
		if (!EV_CheckExec(0x1a))
		{
			return 1;
		}
	}
	if (SeqCheckFlag(0xa6))
	{
		if (!EV_CheckExec(0xd))
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x005adfb0
void NpcMilesSetStandByFlag(long flag)
{
	DAT_05cd14f4 = flag;
}

// STUB: SADX 0x005ae2a0
void * FUN_005ae2a0(void *param_1, unsigned char param_2)
{
	return (void *)0;
}
