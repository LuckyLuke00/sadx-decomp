#include "decls.h"
extern void (*DAT_00a34538[5])(struct task *);
extern int DAT_060df308;
extern void (*DAT_00a34568[4])(struct task *);

#pragma optimize("", off)
// STUB: SADX 0x008b8fa0
void ObjectTikalHint(struct task *task_p)
{
}
#pragma optimize("", on)

// STUB: SADX 0x008b9160
struct task *ObjectTikalBoss(const struct HintMessageString *mes_p, const long adx_index)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x008b9290
void TikalBossKill()
{
	int *local_8;
	if (DAT_060df308 != 0)
	{
		local_8 = *(int **)((char *)DAT_060df308 + 0x20);
		switch (*(char *)local_8)
		{
			case 0:
				*(char *)local_8 = 3;
				break;
			case 1:
				HintMessageStop();
				break;
		}
	}
}

// FUNCTION: SADX 0x008b92e0
void tikal_hint_calc_round(struct NJS_POINT3 *result_vec_p, long ang)
{
	float local_cg;
	float local_8g;
	GetPlayerPosition(0, 0, result_vec_p, 0);
	local_cg = njSin(ang);
	local_8g = njCos(ang);
	result_vec_p->x = local_cg * 15.0 + result_vec_p->x;
	result_vec_p->z = local_8g * 15.0 + result_vec_p->z;
	local_cg = njSin(ang);
	local_8g = njCos(ang);
	result_vec_p->y = (1.0f + local_cg * 0.5) * 5.0 + result_vec_p->y;
}

// FUNCTION: SADX 0x008b9380
void tikal_hint_exec(struct task *task_p)
{
	struct taskwk *local_8;

	local_8 = task_p->twp;
	if (FUN_004c39c0(task_p) != 0)
	{
		njPrintColor(0xffff0000);
		njPrintC(0x110010, "Don't EDIT!");
		njPrintC(0x110011, "Don't EDIT!");
		njPrintC(0x110012, "Don't EDIT!");
		njPrintC(0x110013, "Don't EDIT!");
		njPrintC(0x110014, "Don't EDIT!");
		njPrintColor(0xffc0c0c0);
		njPrintC(0x110015, "<-MessageID");
	}
	LoopTaskC(task_p);
	DAT_00a34538[local_8->mode](task_p);
}

// STUB: SADX 0x008b9450
void tikal_hint_exec_appear(struct task *task_p)
{
}

// STUB: SADX 0x008b9520
void tikal_hint_exec_close(struct task *task_p)
{
}

// FUNCTION: SADX 0x008b9650
void tikal_hint_exec_round(struct task *task_p)
{
	struct taskwk *local_18;
	struct NJS_POINT3 calc_vec;

	local_18 = task_p->twp;
	local_18->timer.l += 0x2b7;
	tikal_hint_calc_round(&calc_vec, local_18->timer.l);
	TikalGotoTarget(&local_18->pos, &calc_vec, 1.0f);
	if (*(signed char *)((char *)local_18 + 3) == 0)
	{
		CancelLookingAtP(0);
		local_18->wtimer = 0xf0;
		local_18->value.f = 1.0f;
		local_18->mode++;
		dsPlay_oneshot_Dolby(0x2f8, (int)task_p, 1, 0, -1, task_p->twp);
	}
}

// STUB: SADX 0x008b9710
void tikal_hint_exec_away(struct task *task_p)
{
}

// FUNCTION: SADX 0x008b98a0
void tikal_hint_exec_idle(struct task *task_p)
{
	struct taskwk *local_8;
	local_8 = task_p->twp;
	if ((short)local_8->wtimer <= 0)
	{
		if (task_p->awp != 0)
			local_8->pos = *(struct NJS_POINT3 *)task_p->awp;
		ObjectTikalHint(task_p);
	}
	else
	{
		local_8->wtimer--;
	}
}

// FUNCTION: SADX 0x008b9910
void tikal_hint_end(struct task *task_p)
{
	dsStop_id((int)task_p);
}

// FUNCTION: SADX 0x008b9930
void tikal_boss_exec(struct task *task_p)
{
	struct taskwk *local_8;
	local_8 = task_p->twp;
	LoopTaskC(task_p);
	(*DAT_00a34568[local_8->mode])(task_p);
}

// STUB: SADX 0x008b9970
void tikal_boss_disappear(struct task *task_p)
{
}

// STUB: SADX 0x008b9a50
void tikal_boss_appear(struct task *task_p)
{
}

// FUNCTION: SADX 0x008b9b60
void tikal_boss_end(struct task *task_p)
{
	DAT_060df308 = 0;
	dsStop_id((int)task_p);
}
