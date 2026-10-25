#include "decls.h"
extern struct NJS_TEXLIST texlist_last1a_highway_a;
extern struct obj object_last1a_highway_a_highway_a;

// FUNCTION: SADX 0x007d52c0
void CLast1AHigh_Disp(struct task *tp)
{
	___njSetTexture(&texlist_last1a_highway_a);
	ds_DrawObjectClip(&object_last1a_highway_a_highway_a, 1.0f);
}

// FUNCTION: SADX 0x007d52e0
void FUN_007d52e0(struct task *param_1)
{
	CLast1AHigh_Disp(param_1);
}

// FUNCTION: SADX 0x007d52f0
void Last1AHigh_Create()
{
	struct task *var1;
	var1 = CreateElementalTask(0, 5, 0);
	if (var1 != 0)
	{
		var1->exec = FUN_007d52e0;
		var1->disp = CLast1AHigh_Disp;
		var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}
