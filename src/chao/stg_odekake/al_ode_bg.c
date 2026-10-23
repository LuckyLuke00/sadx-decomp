#include "decls.h"
extern int DAT_05b3e350;

// STUB: SADX 0x0047ddb0
void BGExecutor(struct task *tp)
{
}

// STUB: SADX 0x0047dfc0
void BGDisplayer(struct task *tp)
{
}

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
