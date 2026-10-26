#include "decls.h"
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);

// STUB: SADX 0x0082dc00
void batDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x0082dda0
void *FUN_0082dda0()
{
	void *var1;
	var1 = MAlloc(0x54);
	memset(var1, 0, 0x54);
	return var1;
}
