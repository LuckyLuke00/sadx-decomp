#include "decls.h"

// FUNCTION: SADX 0x00480580
void CreateCategoryBar(long id, float xpos, float ypos, float size, unsigned short WaitTime)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 3, CategoryBarExecutor);
	var1->disp = CategoryBarDisplayer;
	var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var2 = var1->twp;
	var2->id = (unsigned char)id;
	var2->counter.f = xpos;
	*(int *)((char *)var2 + 0x20) = WaitTime;
	var2->timer.f = ypos;
	*(float *)((char *)var2 + 0x18) = size;
}
