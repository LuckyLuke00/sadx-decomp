#include "decls.h"
void FUN_00572380(struct obj *param_1, struct obj *param_2);
void FUN_005723e0(float param_1);
void FUN_00572f90(struct obj *param_1, struct obj *param_2);
void FUN_00573060(struct NJS_MODEL *param_1, struct obj *param_2);
extern struct obj object_sphere01;

// FUNCTION: SADX 0x00572380
void FUN_00572380(struct obj *param_1, struct obj *param_2)
{
	float local_8;

	local_8 = *(float *)((char *)param_1 + 0x14) * 0.10000000149011612;
	njPushMatrix((float *)0);
	FUN_00572f90(param_1, param_2);
	FUN_005723e0(local_8);
	FUN_00573060(object_sphere01.model, param_1);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005723e0
void FUN_005723e0(float param_1)
{
	FUN_0067d2d0(0, param_1, param_1, param_1);
}

// FUNCTION: SADX 0x00573040
void FUN_00573040(int param_1)
{
	if (*(int *)((char *)param_1 + 8) != 0)
	{
		njRotateZ(0, *(unsigned short *)((char *)param_1 + 8));
	}
	return;
}

// STUB: SADX 0x00573060
void FUN_00573060(struct NJS_MODEL *param_1, struct obj *param_2)
{
}
