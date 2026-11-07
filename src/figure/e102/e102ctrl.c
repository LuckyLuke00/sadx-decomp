#include "decls.h"

// FUNCTION: SADX 0x0061f0f0
void ctrlE102ChangeRun(struct task *tp)
{
	struct taskwk *local_10;
	struct motionwk **local_8g;
	struct motionwk *local_cj;

	local_10 = tp->twp;
	local_8g = (struct motionwk **)tp->mwp;
	local_cj = *local_8g;
	local_cj->height = 0.1f;
	*(float *)((char *)local_cj + 0x40) = 0.0f;
	local_cj->weight = 0.0f;
	local_10->mode = 0x2d;
}
