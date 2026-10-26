#include "decls.h"
void effect_exec(struct task *tp);
void effect_disp(struct task *tp);
extern struct task *DAT_060cc0b0[];
extern struct task *DAT_060cc0b0[1];

// FUNCTION: SADX 0x007d2410
void effect_exec(struct task *tp)
{
	effect_disp(tp);
}

// FUNCTION: SADX 0x007d2670
void effect_exec2(struct task *tp)
{
	effect_disp2(tp);
}

// FUNCTION: SADX 0x007d2680
void effect_delete(short ef_num)
{
	if (DAT_060cc0b0[ef_num])
	{
		DestroyTask(DAT_060cc0b0[ef_num]);
		DAT_060cc0b0[ef_num] = 0;
	}
}

// STUB: SADX 0x007d26b0
void effect_cons(struct task *tp)
{
}

// STUB: SADX 0x007d28f0
void effect_cons2(struct task *tp)
{
}

// FUNCTION: SADX 0x007d2b90
void effect_scl(short ef_num, float sx, float sy)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = DAT_060cc0b0[ef_num];
	if (var1 != 0)
	{
		var2 = var1->twp;
		var2->scl.x = sx;
		var2->scl.y = sy;
	}
}

// FUNCTION: SADX 0x007d2bc0
void effect_color(short ef_num, float col_a, float col_r, float col_g, float col_b)
{
	int *var1 = (int *)DAT_060cc0b0[ef_num];
	if (var1 != 0)
	{
		int *var2 = (int *)(var1[8]);
		int *var3 = (int *)var2[3];
		*(float *)(var3 + 1) = col_a;
		*(float *)(var3 + 2) = col_r;
		*(float *)(var3 + 3) = col_g;
		*(float *)(var3 + 4) = col_b;
	}
}

// STUB: SADX 0x007d2c00
void effect_size_change(short ef_num, float speed_x, float speed_y)
{
}

// STUB: SADX 0x007d2c30
void effect_anim_speed(short ef_num, float anim_speed)
{
}
