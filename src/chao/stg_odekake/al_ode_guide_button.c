#include "decls.h"
void FUN_007d21b0(...);

// FUNCTION: SADX 0x0047e880
void CreateGuideButton(unsigned short id, float xpos, float ypos, unsigned short WaitTime)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 3, GuideButtonExecutor);
	var1->disp = GuideButtonDisplayer;
	var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var2 = var1->twp;
	var2->id = (unsigned char)id;
	var2->counter.f = xpos;
	*(int *)((char *)var2 + 0x20) = WaitTime;
	var2->timer.f = ypos;
}

// FUNCTION: SADX 0x0047e8c0
void CreateKetteiButton(float xpos, float ypos, unsigned short WaitTime)
{
	CreateGuideButton(2, xpos, ypos, WaitTime);
	CreateGuideButton(0, xpos + 55.0, ypos, WaitTime);
}

// FUNCTION: SADX 0x0047e910
void CreateCancelButton(float xpos, float ypos, unsigned short WaitTime)
{
	CreateGuideButton(3, xpos, ypos, WaitTime);
	CreateGuideButton(1, xpos + 55.0, ypos, WaitTime);
}
