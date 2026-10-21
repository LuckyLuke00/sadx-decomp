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
