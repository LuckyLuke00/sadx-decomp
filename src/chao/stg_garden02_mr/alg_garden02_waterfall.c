#include "decls.h"
static void FExec(struct task *tp);

// STUB: SADX 0x0047a710
static void FExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0047a740
void ALG_G02_WaterfallCreate(union NJS_COLOR *pUv, int num)
{
	struct task *var1 = CreateElementalTask(8, 3, FExec);
	if (var1 != 0)
	{
		struct anywk *var2 = var1->awp;
		var2->work.ul[0] = (unsigned long)pUv;
		var2->work.ul[1] = (unsigned long)num;
	}
}
