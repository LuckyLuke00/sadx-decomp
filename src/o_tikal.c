#include "decls.h"
void FUN_005bb770(struct task *param_1);
void FUN_005bb7e0(struct task *param_1);
void FUN_005bb200(struct task *param_1);
void FUN_005bb200(struct task *param_1);
extern void tikal_tubu_draw(struct task *task_p);
void tikal_tubu_draw(struct task *task_p);
void FUN_005bb770(struct task *param_1);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void tikal_illusion_draw(struct task *task_p);
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

// STUB: SADX 0x005bb190
void TikalGotoTarget(struct NJS_POINT3 *from_p, struct NJS_POINT3 *target_p, float speed)
{
}

// STUB: SADX 0x005bb200
void FUN_005bb200(struct task *task_p)
{
}

// STUB: SADX 0x005bb270
void tikal_exec(struct task *task_p)
{
}

// STUB: SADX 0x005bb470
void tikal_tubu_init(struct task *task_p, struct NJS_POINT3 *pos_p, float scale, float alpha)
{
}

// STUB: SADX 0x005bb590
void tikal_tubu_exec(struct task *task_p)
{
}

// FUNCTION: SADX 0x005bb730
void tikal_tubu_draw(struct task *task_p)
{
	struct taskwk *local_8;

	local_8 = task_p->twp;
	tikal_draw_sprite(&sprite_tikal_tubu, (NJS_POINT3 *)((char *)local_8 + 0x20), (NJS_ARGB *)((char *)local_8 + 8), 0, 0.03125f);
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

// STUB: SADX 0x005bb820
void tikal_draw_sprite(struct NJS_SPRITE *spr_p, struct NJS_POINT3 *pos_p, struct NJS_ARGB *argb_p, long frame, float scale)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njSetConstantMaterial(argb_p);
	spr_p->p = *pos_p;
	spr_p->sx = scale;
	spr_p->sy = scale;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	if (((DAT_025acd84 & 2) >> 1) != 0 && (DAT_025acd84 & 1) != 0)
	{
		___njFogDisable();
	}
	if (tikal_sw != 0)
	{
		*(float *)&DAT_05b3df40 = 20048.0f;
	}
	late_DrawSprite3D(spr_p, frame, 0x32, 1);
	*(float *)&DAT_05b3df40 = 0.0f;
	if (((DAT_025acd84 & 2) >> 1) != 0 && (DAT_025acd84 & 1) != 0)
	{
		___njFogEnable();
	}
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	ResetMaterial();
}

// STUB: SADX 0x005bb910
void FUN_005bb910(struct task *task_p, struct NJS_POINT3 *pos_p, void *ptr_p, int bt)
{
}

// STUB: SADX 0x005bb9d0
void FUN_005bb9d0(struct task *task_p)
{
}

// FUNCTION: SADX 0x005bbac0
void tikal_illusion_draw(struct task *task_p)
{
	struct taskwk *local_8g = task_p->twp;

	tikal_draw_sprite(&sprite_tikal_tubu, &local_8g->pos, (NJS_ARGB *)((char *)local_8g + 8), 0, local_8g->scl.x * 0.125f);
}
