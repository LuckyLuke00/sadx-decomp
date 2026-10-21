#include "decls.h"

// STUB: SADX 0x005c1a30
void FUN_005c1a30(int param_1)
{
}

// STUB: SADX 0x005c2a80
void FUN_005c2a80(struct task *tp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c2b10
void CallLeonDraw(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	LeonDraw(local_cg, local_8g);
}

// FUNCTION: SADX 0x005c2b40
void CallLeonDrawLink(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	LeonDrawLink(local_cg, (struct enemywk *)local_8g);
}
