#include "decls.h"
static void FDisp(struct task *tp);

// FUNCTION: SADX 0x004720e0
static void FDisp(struct task *tp)
{
	struct anywk *var1;

	if (DAT_05b9d838 == 0)
	{
		var1 = tp->awp;
		late_exec();
		___njSetTexture(&texlist_chao_entrance);
		FUN_004a7cb0((struct obj *)&object_crch_nc_spotlight_all_nc_spotlight_all, (struct NJS_MOTION *)&motion_crch_nc_spotlight_all, var1->work.f[0]);
	}
}

// FUNCTION: SADX 0x00472120
void FUN_00472120(struct task *param_1)
{
	struct anywk *var1;

	var1 = param_1->awp;
	var1->work.f[0] = var1->work.f[0] + 0.019999999552965164;
	if (var1->work.f[0] >= 8.0f)
	{
		var1->work.f[0] = 0.0f;
	}
	FDisp(param_1);
}

// FUNCTION: SADX 0x00472160
void FUN_00472160()
{
	struct task *var1 = CreateElementalTask(8, 2, FUN_00472120);
	var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var1->disp = FDisp;
}
