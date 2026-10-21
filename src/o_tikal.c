#include "decls.h"
void FUN_005bb770(struct task *param_1);
void FUN_005bb7e0(struct task *param_1);
void njSubVector(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2);
void njAddVector(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2);
void FUN_005bb9d0(struct task *param_1);
void FUN_005bb910(struct task *param_1, struct NJS_POINT3 *param_2, void *param_3, int param_4);

// STUB: SADX 0x005bb090
struct task *TikalMake(struct task *par_task_p, struct task **child_task_pp, struct NJS_POINT3 *pos_p)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x005bb100
void TikalSetParameter(struct task *tikal_task_p, float scale, float alpha)
{
	struct taskwk *local_8;

	if (tikal_task_p != NULL)
	{
		local_8 = tikal_task_p->twp;
		local_8->counter.f = alpha;
		local_8->scl.x = scale;
	}
}

// FUNCTION: SADX 0x005bb130
void TikalSetIllusion(struct task *tikal_task_p)
{
	struct taskwk *local_8g;
	struct task *local_cg;

	if (tikal_task_p != 0)
	{
		local_8g = tikal_task_p->twp;
		local_cg = CreateElementalTask(2, 6, FUN_005bb9d0);
		if (local_cg != 0)
		{
			FUN_005bb910(local_cg, &local_8g->pos, (void *)((char *)local_8g + 8), (int)(signed char)local_8g->btimer);
		}
	}
}

// FUNCTION: SADX 0x005bb190
void TikalGotoTarget(struct NJS_POINT3 *from_p, struct NJS_POINT3 *target_p, float speed)
{
	NJS_POINT3 local_14;

	njSubVector(target_p, from_p);
	ghUnitVector(target_p, target_p);
	target_p->x = target_p->x * speed;
	target_p->y = target_p->y * speed;
	target_p->z = target_p->z * speed;
	njAddVector(from_p, target_p);
}

// STUB: SADX 0x005bb200
void FUN_005bb200(struct task *task_p)
{
}

// STUB: SADX 0x005bb730
void tikal_tubu_draw(struct task *task_p)
{
}

// STUB: SADX 0x005bb770
void FUN_005bb770(struct task *ptp)
{
}

// FUNCTION: SADX 0x005bb7e0
void FUN_005bb7e0(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (*(int *)((char *)local_8 + 0x34) != 0)
	{
		*(int *)*(int *)((char *)local_8 + 0x34) = 0;
	}
}

// FUNCTION: SADX 0x005bb810
void tikal_dispSwitch(int sw)
{
	tikal_sw = sw;
}

// STUB: SADX 0x005bbac0
void tikal_illusion_draw(struct task *task_p)
{
}
