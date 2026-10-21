#include "decls.h"

// FUNCTION: SADX 0x008de9d0
void FUN_008de9d0(struct task *param_1)
{
	FUN_004c39c0(param_1);
}

// STUB: SADX 0x008dea80
void dispBuyon(struct task *tp)
{
}

// STUB: SADX 0x008df990
void dispBuyonBody(struct task *tp)
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
	(*(void (*)(struct task *, struct taskwk *, struct motionwk *))FUN_005b5aa0)(tp, local_cg, local_8g);
}
