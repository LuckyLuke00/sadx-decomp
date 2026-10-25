#include "decls.h"

// FUNCTION: SADX 0x005c5a30
void FUN_005c5a30(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	*(float *)((char *)local_8 + 0x30) -= 0.4f;
	if ((local_8->flag & 0x100) && param_1->ctp && (*(char *)param_1->ctp->twp == 0xc))
	{
		*(float *)((char *)param_1->ctp->twp + 0x24) -= 0.4f;
	}
	if (*(float *)((char *)local_8 + 0x30) < -40.0f)
	{
		*(float *)((char *)local_8 + 0x30) = -40.0f;
		local_8->mode = 5;
		local_8->wtimer = 0;
	}
	AirLiftDraw(param_1);
}

// FUNCTION: SADX 0x005c5ae0
void FUN_005c5ae0(struct task *param_1)
{
	struct taskwk *local_8 = param_1->twp;
	local_8->scl.x = local_8->scl.x - 0.44999998807907104;
	if (local_8->scl.x < 0.0)
	{
		local_8->scl.x = 0.0;
		local_8->mode = 0;
		local_8->wtimer = 0;
	}
	AirLiftDraw(param_1);
}
