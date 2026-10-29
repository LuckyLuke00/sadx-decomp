#include "decls.h"
extern struct obj object_cylinder01[];

// FUNCTION: SADX 0x006c0ba0
static void FUN_006c0ba0(long param_1)
{
	switch (param_1)
	{
	case 0:
		SetEntranceNumber(0);
		InitFreeCamera();
		SeqChangeStage(0x22, 1);
		break;
	case 1:
		SetEntranceNumber(0);
		InitFreeCamera();
		SeqChangeStage(0x22, 0);
		break;
	}
}

// FUNCTION: SADX 0x006c0be0
void CollisionPastSceneChanger(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float local_8;
	float var2;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (FUN_004c39c0(tp))
	{
		njPushMatrix(0);
		var2 = var1->scl.x * 0.1f;
		local_8 = var1->scl.y * 0.1f;
		FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
		SetMaterial(0.1f, 1.0f, 0.8f, 0.2f);
		FUN_0067d2d0(0, var2, local_8, var2);
		ds_DrawObjectClip(object_cylinder01, var2 > local_8 ? var2 : local_8);
		njPopMatrix(1);
		ResetMaterial();
		return;
	}
	if (CheckCollisionCylinderP(&var1->pos, var1->scl.x, var1->scl.y) == 1)
	{
		FUN_006c0ba0(var1->ang.x);
		DeadOut(tp);
	}
}
