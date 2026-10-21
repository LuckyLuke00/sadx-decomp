#include "decls.h"

// FUNCTION: SADX 0x005cdd30
void PoliceDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	PoliceDraw(local_cg, local_8g);
}

// STUB: SADX 0x005cf4f0
void FUN_005cf4f0(struct task *pTask, void *param_2, void *param_3)
{
}

// STUB: SADX 0x005cfef0
void PoliceTurnSlow(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005cfff0
void PoliceTurnHead(struct taskwk *twp, struct enemywk *ewp)
{
	long local_8g;

	local_8g = SubAngle(ewp->aim_angle, twp->ang.y);
	local_8g = (local_8g + 0x8000) & 0xffff;
	if (local_8g < 0x400f)
	{
		local_8g = 0x400f;
	}
	else if (local_8g > 0xbff0)
	{
		local_8g = 0xbff0;
	}
	local_8g = (local_8g + 0x8000) & 0xffff;
	ewp->sub_angle[1] = AdjustAngle(ewp->sub_angle[1], -local_8g, 0x360);
}

// STUB: SADX 0x005d01b0
void PoliceTurn(struct taskwk *twp, struct enemywk *ewp)
{
}
