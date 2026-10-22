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

// STUB: SADX 0x004817c0
void CreateOdekakePortWindow(long PortNum, float xpos, float ypos, unsigned short WaitTime)
{
}
