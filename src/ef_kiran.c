#include "decls.h"

// STUB: SADX 0x0054fdc0
void effectKiran(struct sp_task *tp, struct sp_link *lp)
{
}

// FUNCTION: SADX 0x0054fec0
void CreateKiran2(struct NJS_POINT3 *pos, float scl, float spd)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	local_cg = CreateElementalTask(2, 3, effectKiran2);
	if (local_cg != NULL)
	{
		local_8g = local_cg->twp;
		local_cg->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
		local_cg->disp = drawEffectKiran2;
		local_8g->scl.x = scl * 0.10000000149011612;
		local_8g->scl.z = 0.0f;
		local_8g->value.f = spd;
		local_8g->pos = *pos;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0054ff40
void effectKiran2(struct task *tp)
{
}
#pragma optimize("", on)
