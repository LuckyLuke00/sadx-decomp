#include "decls.h"
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x006f1d30
void Choas4ArmFlagSet(struct obj *obj, long hide)
{
	do
	{
		if (hide != 0)
		{
			obj->evalflags |= 8;
		}
		else
		{
			obj->evalflags &= 0xfffffff7;
		}
		if (obj->child != 0)
		{
			Choas4ArmFlagSet(obj->child, hide);
		}
		obj = obj->sibling;
	}
	while (obj != 0);
}

// FUNCTION: SADX 0x006f1d70
void ArmTestDisplay(struct obj *obj)
{
	do
	{
		njPushMatrix((float *)0);
		FUN_0067d830((float *)0, obj->pos[0], obj->pos[1], obj->pos[2]);
		if (obj->ang[2] != 0)
		{
			njRotateZ((float *)0, (unsigned short)obj->ang[2]);
		}
		if (obj->ang[0] != 0)
		{
			njRotateX((float *)0, (unsigned short)obj->ang[0]);
		}
		if (obj->ang[1] != 0)
		{
			njRotateY((float *)0, (unsigned short)obj->ang[1]);
		}
		FUN_0067d2d0((float *)0, obj->scl[0], obj->scl[1], obj->scl[2]);
		if (obj->model != 0)
		{
			CHAOS_DrawModel(obj->model);
		}
		if (obj->child != 0)
		{
			ArmTestDisplay(obj->child);
		}
		njPopMatrix(1);
		obj = obj->sibling;
	}
	while (obj != 0);
}
