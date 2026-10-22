#include "decls.h"
struct pathtag;
struct pathinfo;
struct pathtbl;
void CalcPNNPntParam(struct pathtag *tag, struct pathinfo *pi, long pnmb, struct pathtbl *pt);
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x0056fd90
unsigned long InitPathWork()
{
	struct task *local_8g;
	struct taskwk *local_cg;

	local_8g = CreateElementalTask(2, 2, ManagePathWork);
	if (local_8g != 0)
	{
		local_cg = local_8g->twp;
		*(unsigned short *)((char *)local_cg + 0xc) = (DAT_05b9d724 << 8) | DAT_05b9d744;
		return 1;
	}
	return 0;
}

// STUB: SADX 0x00570230
void CalcPNNPntParam(struct pathtag *tag, struct pathinfo *pi, long pnmb, struct pathtbl *pt)
{
}
