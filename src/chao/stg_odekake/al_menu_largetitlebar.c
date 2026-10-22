#include "decls.h"

// FUNCTION: SADX 0x00480110
void CreateLargeTitleBar(long id, float xpos, float ypos)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 3, LargeTitleBarExecutor);
	var1->disp = LargeTitleBarDisplayer;
	var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var2 = var1->twp;
	var2->counter.f = xpos;
	var2->id = (unsigned char)id;
	var2->timer.f = ypos;
}
