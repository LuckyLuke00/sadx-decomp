#include "decls.h"
extern struct NJS_ACTION action_stol_s_pyo_born_b[1];
extern struct NJS_ACTION action_l_walk_s_pyo_born_b[1];
extern struct NJS_ACTION action_ltos_s_pyo_born_b[1];

// STUB: SADX 0x008de820
void execBuyonHead(struct task *tp)
{
}

// FUNCTION: SADX 0x008de9d0
void FUN_008de9d0(struct task *param_1)
{
	FUN_004c39c0(param_1);
}

// STUB: SADX 0x008de9f0
void dispBuyonSub(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x008dea80
void dispBuyon(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x008df8f0
void dispBuyonSub_Jel(struct task *tp)
{
}

// STUB: SADX 0x008df990
void dispBuyonBody(struct task *tp)
{
}

// FUNCTION: SADX 0x008dfa00
void execBuyonBornB(struct task *tp)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->ptp->twp;
	local_cg->pos = local_8g->pos;
	local_cg->ang = local_8g->ang;
	switch (local_cg->mode)
	{
	case 0:
		local_cg->mode = 1;
		local_cg->counter.ptr = &action_stol_s_pyo_born_b;
		tp->dest = FUN_008de9d0;
		break;
	case 1:
		if (local_8g->mode == 3)
		{
			local_cg->mode = 3;
			local_cg->counter.ptr = &action_stol_s_pyo_born_b;
			tp->disp = dispBuyonSub;
			local_cg->timer.f = 0.0f;
		}
		break;
	case 3:
		dispBuyon(tp);
		if (local_8g->mode == 4)
		{
			local_cg->mode = 4;
			local_cg->counter.ptr = &action_l_walk_s_pyo_born_b;
			local_cg->timer.f = 0.0f;
		}
		break;
	case 4:
		dispBuyon(tp);
		if (local_8g->mode == 5)
		{
			local_cg->mode = 5;
			local_cg->counter.ptr = &action_ltos_s_pyo_born_b;
			local_cg->timer.f = 0.0f;
		}
		break;
	case 5:
		dispBuyon(tp);
		if (local_8g->mode == 1 || local_8g->mode == 2)
		{
			local_cg->mode = 1;
			tp->disp = 0;
			local_cg->timer.f = 0.0f;
		}
		break;
	}
}

// STUB: SADX 0x008dfb80
void execBuyonBornA(struct task *tp)
{
}

// STUB: SADX 0x008dfd10
void execBuyonWaist(struct task *tp)
{
}

// FUNCTION: SADX 0x008e07d0
void exitBuyonManager(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	FreeTaskC(tp);
	FUN_005b5aa0(tp, local_cg, local_8g);
}

// STUB: SADX 0x008e0810
void dispBuyonShadow(struct task *tp)
{
}

// STUB: SADX 0x008e09e0
void calcAimPos(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x008e0f50
void reviseBuyonPosition(struct task *tp)
{
}

// STUB: SADX 0x008e11e0
void checkBuyonColli(struct task *tp)
{
}

// STUB: SADX 0x008e1430
long searchPlayer(struct task *tp)
{
	return (long)0;
}
