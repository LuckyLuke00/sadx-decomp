#include "decls.h"
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
