#include "decls.h"

// FUNCTION: SADX 0x0047e5c0
void CreateDecideButton(long id, long cursorX, long cursorY, float xpos, float ypos, unsigned short WaitTime)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 3, DecideButtonExecutor);
	var1->disp = DecideButtonDisplayer;
	var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var2 = var1->twp;
	var2->id = (unsigned char)id;
	var2->counter.f = xpos;
	*(int *)((char *)var2 + 0x20) = WaitTime;
	var2->timer.f = ypos;
	*(int *)((char *)var2 + 0x24) = cursorX;
	*(int *)((char *)var2 + 0x28) = cursorY;
}
