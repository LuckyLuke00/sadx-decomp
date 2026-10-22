#include "decls.h"
extern int DAT_05b3e350;

// FUNCTION: SADX 0x0047e070
void BGDestructor(struct task *tp)
{
	DAT_05b3e350 = 0;
}

// FUNCTION: SADX 0x0047e080
void CreateOdeBG()
{
	struct task *var1 = CreateElementalTask(8, 2, BGExecutor);
	var1->disp = BGDisplayer;
	var1->dest = BGDestructor;
	var1->awp->work.f[0] = 0.0f;
	var1->awp->work.f[1] = 0.0f;
	var1->awp->work.f[2] = 1.0f;
}
