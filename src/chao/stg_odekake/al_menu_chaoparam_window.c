#include "decls.h"
extern int DAT_05b33100;

// FUNCTION: SADX 0x0047fb20
void ChaoParamWindowDestructor(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(struct task **)((char *)var1 + 0x24))
	{
		FreeTask(*(struct task **)((char *)var1 + 0x24));
		*(struct task **)((char *)var1 + 0x24) = 0;
	}
	DAT_05b33100 = 0;
}

// FUNCTION: SADX 0x0047fb50
void ChaoParamWindowSetDecidedFlag()
{
	*(char *)((char *)*(int *)((char *)DAT_05b33100 + 0x20) + 3) = 1;
}

// STUB: SADX 0x0047fb60
void CreateChaoParamWindow(float xpos, float ypos, unsigned short WaitTime)
{
}
