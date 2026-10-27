#include "decls.h"
void effect2_disp(struct task *tp);
void effect2_exec(struct task *tp);
void effect2_dest(struct task *tp);
extern int DAT_060cc790[1];

// FUNCTION: SADX 0x007d72a0
void effect2_exec(struct task *tp)
{
	effect2_disp(tp);
}

// FUNCTION: SADX 0x007d72b0
void effect2_dest(struct task *tp)
{
	if (tp->twp->timer.ptr)
	{
		Free(tp->twp->timer.ptr);
	}
}

// STUB: SADX 0x007d7300
void effect2_cons(struct task *tp)
{
}

// FUNCTION: SADX 0x007d7590
void effect2_scl(short ef_num, float sx, float sy)
{
	int *var1 = (int *)DAT_060cc790[ef_num];
	if (var1 != 0)
	{
		int *var2 = (int *)(var1[8]);
		*(float *)(var2 + 11) = sx;
		*(float *)(var2 + 12) = sy;
	}
}

// FUNCTION: SADX 0x007d75c0
void effect2_color(short ef_num, float col_a, float col_r, float col_g, float col_b)
{
	int *var1 = (int *)DAT_060cc790[ef_num];
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

// FUNCTION: SADX 0x007d7600
void effect2_angle(short ef_num, long ang_start, long ang_speed)
{
	int *var1 = (int *)DAT_060cc790[ef_num];
	if (var1 != 0)
	{
		int *var2 = (int *)(var1[8]);
		var2[5] += ang_start;
		int *var3 = (int *)var2[3];
		var3[5] = ang_speed;
	}
}

// FUNCTION: SADX 0x007d7630
void effect2_size_change(short ef_num, float speed_x, float speed_y)
{
	int *var1 = (int *)DAT_060cc790[ef_num];
	if (var1 != 0)
	{
		int *var2 = (int *)(var1[8]);
		int *var3 = (int *)var2[3];
		*(float *)(var3 + 6) = speed_x;
		*(float *)(var3 + 7) = speed_y;
	}
}
