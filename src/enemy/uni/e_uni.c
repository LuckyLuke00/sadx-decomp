#include "decls.h"

// FUNCTION: SADX 0x005cd410
void UniCDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	UniCDraw(local_cg, local_8g);
}
