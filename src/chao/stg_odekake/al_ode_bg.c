#include "decls.h"
extern void *DAT_05b330e4;
extern int DAT_05b3e350;

// FUNCTION: SADX 0x0047ddb0
void BGExecutor(struct task *tp)
{
	struct anywk *var1;
	float var2;
	float var3;
	void (*var4)(struct task *);

	var1 = tp->awp;
	if (DAT_05b330e4 == 0)
	{
		FreeTask(tp);
		return;
	}
	var2 = var1->work.f[0] - 0.4000000059604645;
	var1->work.f[0] = var2;
	var3 = var1->work.f[1] + 0.5;
	var1->work.f[1] = var3;
	if (var2 < -210.0)
		var1->work.f[0] = var2 + 210.0;
	if (var3 >= 0.0)
		var1->work.f[1] = var3 - 210.0;
	if (*(int *)((char *)DAT_05b330e4 + 4) == 0)
	{
		var2 = var1->work.f[2] + 0.05000000074505806;
		var1->work.f[2] = var2;
		if (var2 > 1.0)
			var1->work.f[2] = 1.0;
	}
	else
	{
		var2 = var1->work.f[2] - 0.05000000074505806;
		var1->work.f[2] = var2;
		if (var2 < 0.0)
			var1->work.f[2] = 0.0;
	}
	var4 = tp->disp;
	var4(tp);
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
