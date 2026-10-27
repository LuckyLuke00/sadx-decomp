#include "decls.h"

// FUNCTION: SADX 0x00480fc0
void ToridasuPortWindowDestructor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (*(void **)((char *)var1 + 0x28) != 0)
	{
		FreeTask((struct task *)*(void **)((char *)var1 + 0x28));
		*(void **)((char *)var1 + 0x28) = 0;
	}
}

// FUNCTION: SADX 0x00480ff0
void CreateToridasuPortWindow(long PortNum, float xpos, float ypos, unsigned short WaitTime)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 3, ToridasuPortWindowExecutor);
	var1->disp = ToridasuPortWindowDisplayer;
	var1->dest = ToridasuPortWindowDestructor;
	var2 = var1->twp;
	var2->id = (unsigned char)PortNum;
	var2->counter.f = xpos;
	*(int *)((char *)var2 + 0x20) = WaitTime;
	var2->timer.f = ypos;
}
