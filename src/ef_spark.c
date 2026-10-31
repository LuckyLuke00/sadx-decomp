#include "decls.h"
extern short DAT_05b9d73c;

// FUNCTION: SADX 0x0060fcb0
void CreateSpark(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	if (DAT_05b9d73c == 0x10)
		return;
	local_cg = CreateElementalTask(2, 6, EffectSpark);
	if (local_cg != NULL)
	{
		local_8g = local_cg->twp;
		local_8g->wtimer = 0;
		local_8g->pos = *pos;
		local_8g->scl = *velo;
	}
}

// STUB: SADX 0x0060fd30
void EffectSpark(struct task *tp)
{
}
