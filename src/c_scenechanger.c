#include "decls.h"

static void CollisionSceneChangerRegular(struct task *tp);

// FUNCTION: SADX 0x008e1c90
void CollisionSceneChanger(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;
	float local_cj;
	float local_10;
	float local_14q;
	// GLOBAL: SADX 0x04c7bda0
	static struct CCL_INFO DAT_04c7bda0[1] =
	{
		{ 0, 3, 0xb0, 0, 0, { 0.0f, 0.0f, 0.0f }, 5.0f, 5.0f, 5.0f, 0.0f, 0, 0, 0 }
	};

	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, DAT_04c7bda0, 1, 6);
		local_cj = (local_8g->scl.x += 1.0) * 5.0;
		local_10 = (local_8g->scl.y += 1.0) * 5.0;
		local_14q = (local_8g->scl.z += 1.0) * 5.0;
		local_8g->cwp->info->a = local_cj;
		local_8g->cwp->info->b = local_10;
		local_8g->pos.y = local_10 + local_8g->pos.y;
		local_8g->cwp->info->c = local_14q;
		SET_COLLI_RANGE(local_8g->cwp, local_cj * local_cj + local_10 * local_10 + local_14q * local_14q);
	}
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = CollisionSceneChangerRegular;
}

// STUB: SADX 0x008e1dc0
static void CollisionSceneChangerRegular(struct task *tp)
{
}
