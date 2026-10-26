#include "decls.h"
extern struct NJS_SPRITE sprite_lensflare;
void FUN_005b5aa0(...);
static void LensFlareExecutor(struct task *tp);
void LensFlareExecutor(struct task *tp);

// FUNCTION: SADX 0x005e00f0
void EffectLensFlare(struct task *tp)
{
	struct NJS_SPRITE *local_8;
	local_8 = &sprite_lensflare;
	tp->exec = LensFlareExecutor;
	tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
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
