#include "decls.h"

// FUNCTION: SADX 0x00481790
void OdekakePortWindowDestructor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = (struct task *)(*(int *)((char *)var1 + 0x24));
	if (var2 != NULL)
	{
		FreeTask(var2);
		*(int *)((char *)var1 + 0x24) = 0;
	}
}

// FUNCTION: SADX 0x004817c0
void CreateOdekakePortWindow(long PortNum, float xpos, float ypos, unsigned short WaitTime)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 3, OdekakePortWindowExecutor);
	var1->disp = OdekakePortWindowDisplayer;
	var1->dest = OdekakePortWindowDestructor;
	var2 = var1->twp;
	var2->id = (unsigned char)PortNum;
	var2->counter.f = xpos;
	*(int *)((char *)var2 + 0x20) = WaitTime;
	var2->timer.f = ypos;
}
