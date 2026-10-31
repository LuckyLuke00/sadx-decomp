#include "decls.h"
static void EffectBomb(struct sp_task *tp, struct sp_link *lp);
extern struct particle_entry particle_bomb;
extern struct particle_info default_bomb;

// FUNCTION: SADX 0x0060d560
void FUN_0060d560(struct NJS_POINT3 *param_1, float param_2)
{
	struct sp_link *local_8g;
	struct sp_task *local_cg;

	local_8g = particle_bomb.link;
	local_cg = SpCreateTask(local_8g, EffectBomb);
	if (local_cg != NULL)
	{
		local_cg->pos = *param_1;
		local_cg->scl = param_2 * 0.5f;
		local_cg->frame = 0.0f;
		local_cg->ang = 0;
		local_cg->argb = default_bomb.argb;
		local_cg->work[0].ptr = &default_bomb;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0060d600
static void EffectBomb(struct sp_task *tp, struct sp_link *lp)
{
}
#pragma optimize("", on)
