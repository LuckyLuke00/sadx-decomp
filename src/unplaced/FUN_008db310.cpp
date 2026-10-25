#include "decls.h"
extern int DAT_05b9d838;

// STUB: SADX 0x008db310
void FUN_008db310(int param_1, float *param_2)
{
}

// FUNCTION: SADX 0x008db3d0
void FUN_008db3d0(struct obj *param_1)
{
	float local_8;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	local_8 = *(float *)((char *)param_1 + 0x34);
	if (local_8 < 60.0f)
	{
		local_8 = 60.0f;
	}
	else if (local_8 > 150.0f)
	{
		local_8 = 150.0f;
	}
	___dsSetPalette(6);
	njPushMatrix(0);
	FUN_0067d830(0, param_1->scl[0], param_1->scl[1], param_1->scl[2]);
	if (param_1->ang[1] != 0)
	{
		njRotateY(0, (unsigned short)param_1->ang[1]);
	}
	if (1 != 0)
	{
		njRotateY(0, 0xc000);
	}
	___njSetTexture(&texlist_e_snake);
	___dsDrawObject(&object_snake_head_head[0]);
	njPopMatrix(1);
	___dsSetPalette(0);
}
