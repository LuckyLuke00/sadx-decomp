#include "decls.h"
extern struct task *DAT_060cc154;

// STUB: SADX 0x007d40a0
void SetEffectRotaryEmerald(int eme_num, struct NJS_TEXLIST *ef_name, float scale, float col_a, float col_r, float col_g, float col_b)
{
}

// FUNCTION: SADX 0x007d4120
void FUN_007d4120(int param_1)
{
	struct taskwk *local_8 = DAT_060cc154->twp;
	if (*(int *)((char *)local_8->value.ptr + param_1 * 4 - 4) != 0)
	{
		effect_delete(--param_1);
	}
}

// FUNCTION: SADX 0x007d4500
void destRotaryEmeraldTask(struct task *task_p)
{
	int var1;
	void *var2 = task_p->twp->value.ptr;

	for (var1 = 0; var1 < 7; var1++)
	{
		effect_delete(var1);
	}
	if (var2)
	{
		Free(var2);
	}
}

// FUNCTION: SADX 0x007d4670
void CreateRotaryEmerald(float pos_x, float pos_y, float pos_z, float r, long rot_spd, struct task *eme1_task_p, struct task *eme2_task_p, struct task *eme3_task_p, struct task *eme4_task_p, struct task *eme5_task_p, struct task *eme6_task_p, struct task *eme7_task_p)
{
	struct NJS_POINT3 pos;
	struct task *eme_task_p[7];
	pos.x = pos_x;
	pos.y = pos_y;
	pos.z = pos_z;
	g_EmeraldRotSpd = rot_spd;
	g_RotaryCircleR = r;
	eme_task_p[0] = eme1_task_p;
	eme_task_p[1] = eme2_task_p;
	eme_task_p[2] = eme3_task_p;
	eme_task_p[3] = eme4_task_p;
	eme_task_p[4] = eme5_task_p;
	eme_task_p[5] = eme6_task_p;
	eme_task_p[6] = eme7_task_p;
	createRotaryEmeraldTask(pos, eme_task_p);
}
