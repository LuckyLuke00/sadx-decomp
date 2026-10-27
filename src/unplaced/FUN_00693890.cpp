#include "decls.h"
extern struct NJS_MODEL DAT_05a862b0;
struct task;
struct NJS_MODEL;

// FUNCTION: SADX 0x00693890
void FUN_00693890(struct task *param_1, float param_2)
{
	struct taskwk *var3;
	float local_18;
	float var1;
	struct NJS_POINT3 var2;
	var3 = param_1->twp;
	local_18 = GetShadowPos(var3->pos.x, var3->pos.y, var3->pos.z, (struct Angle3 *)&var2);
	local_18 += 0.6000000238418579;
	SetRegularTexture();
	njPushMatrix(0);
	var1 = param_2 * 0.25;
	FUN_0067d830(0, var3->pos.x, local_18, var3->pos.z);
	FUN_0067d2d0(0, var1, var1, var1 * 0.800000011920929);
	___dsDrawModel(&DAT_05a862b0);
	njPopMatrix(1);
}
