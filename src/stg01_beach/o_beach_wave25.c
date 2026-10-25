#include "decls.h"
extern float DAT_060ceab0[96];

// FUNCTION: SADX 0x008018f0
void CreateRippleSource25(struct task *tp, float pp_x, float pp_z, float start_rad, float end_rad, float scl)
{
	struct taskwk *var1 = tp->twp;
	int var2 = (int)var1->counter.l;
	if ((unsigned)var2 < 0x1e)
	{
		var1->counter.l = var2 + 1;
		float *var3 = &DAT_060ceab0[var2 * 6];
		var3[0] = pp_x;
		var3[1] = pp_z;
		var3[2] = scl;
		var3[3] = start_rad * 436.90667724609375f;
		var3[4] = end_rad * 436.90667724609375f;
		var3[5] = 200.0f;
	}
}
