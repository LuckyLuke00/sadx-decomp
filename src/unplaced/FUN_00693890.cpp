#include "decls.h"
struct task;
struct NJS_MODEL;

// FUNCTION: SADX 0x00693890
void FUN_00693890(struct task *param_1, float param_2)
{
	struct taskwk *var1 = param_1->twp;
	float local_1c;
	float local_18;
	struct Angle3 local_14;
	local_18 = GetShadowPos(var1->pos.x, var1->pos.y, var1->pos.z, &local_14) + 0.6000000238418579;
	SetRegularTexture();
	njPushMatrix(0);
	local_1c = param_2 * 0.25;
	FUN_0067d830(0, var1->pos.x, local_18, var1->pos.z);
	FUN_0067d2d0(0, local_1c, local_1c, local_1c * 0.800000011920929);
	___dsDrawModel((struct NJS_MODEL *)0x5a862b0);
	njPopMatrix(1);
}
