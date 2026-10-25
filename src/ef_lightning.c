#include "decls.h"

// FUNCTION: SADX 0x0060ceb0
void CreateLightning(struct NJS_POINT3 *pos, float scl)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;

	local_8gk = particle_lightning.link;
	local_ci = SpCreateTask(local_8gk, EffectLightning);
	if (local_ci != NULL)
	{
		local_ci->pos = *pos;
		local_ci->scl = scl * 0.15000000596046448;
		local_ci->frame = 0.0;
		local_ci->ang = 0;
		local_ci->argb.a = 1.0;
		local_ci->argb.r = 1.0;
		local_ci->argb.g = 1.0;
		local_ci->argb.b = 1.0;
	}
}

// FUNCTION: SADX 0x0060cf40
void EffectLightning(struct sp_task *tp, struct sp_link *lp)
{
	tp->no = (short)(int)(tp->frame);
	if (tp->no >= 8)
	{
		tp->no = 7;
		SpFreeTask(tp);
	}
	else
	{
		tp->frame = tp->frame + 1.0f;
	}
}
