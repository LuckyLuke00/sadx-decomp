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

// STUB: SADX 0x00480ff0
void CreateToridasuPortWindow(long PortNum, float xpos, float ypos, unsigned short WaitTime)
{
}
