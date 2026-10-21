#include "decls.h"
void LensFlareExecutor(struct task *tp);

// STUB: SADX 0x005e00f0
void EffectLensFlare(struct task *tp)
{
}

// FUNCTION: SADX 0x005e0600
void LensFlareExecutor(struct task *tp)
{
	DrawLensFlare(&tp->twp->pos);
}

// FUNCTION: SADX 0x005e0620
void CreateLensFlare(struct NJS_POINT3 *pos)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	local_cg = CreateElementalTask(2, 4, EffectLensFlare);
	if (local_cg != NULL) {
		local_8g = local_cg->twp;
		local_8g->pos = *pos;
	}
}
