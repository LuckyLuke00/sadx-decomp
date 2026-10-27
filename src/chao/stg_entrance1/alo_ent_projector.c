#include "decls.h"
static void FExec(struct task *tp);
static void FDisp(struct task *tp);

// FUNCTION: SADX 0x00472180
static void FDisp(struct task *tp)
{
	struct anywk *var1;
	float var2;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	var1 = tp->awp;
	var2 = (float)var1->work.ub[14];
	var2 = var2 * 2.0f;
	___njSetTexture(&texlist_chao_entrance);
	FUN_004a7cb0((struct obj *)&object_crch_nc_projector_a_nc_projector_a, (struct NJS_MOTION *)&motion_crch_nc_projector_a, var2);
	FUN_004a7cb0((struct obj *)&object_crch_nc_projector_b_nc_projector_b, (struct NJS_MOTION *)&motion_crch_nc_projector_b, var2);
	AlgKinderOrthoQPolyBegin();
	AlgKinderOrthoQPolyDrawZ(0.0f, ScreenRaitoX * 640.0, 0.0f, ScreenRaitoY * 480.0, -1000.0f, 0);
	AlgKinderOrthoEnd();
}

// FUNCTION: SADX 0x00472240
static void FExec(struct task *tp)
{
	struct anywk *var1 = tp->awp;
	var1->work.ub[15] += 1;
	if (var1->work.ub[15] == 15)
	{
		var1->work.ub[14] += 1;
		var1->work.ub[15] = 0;
		if (var1->work.ub[14] == 4)
		{
			var1->work.ub[14] = 0;
		}
	}
	FDisp(tp);
}

// FUNCTION: SADX 0x00472270
void FUN_00472270()
{
	struct task *var1 = CreateElementalTask(8, 2, FExec);
	var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var1->disp = FDisp;
}
