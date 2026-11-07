#include "decls.h"
static void Normal(struct task *pTask);

// FUNCTION: SADX 0x00821070
static void Normal(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	if (CheckRangeOut(pTask) != 0)
	{
		return;
	}
	FUN_00422560(3);
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)var1->ang.x);
	}
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	if ((int)var1->counter.l != 0)
	{
		if ((int)var1->counter.l == 3)
		{
			SetObjectTexture();
			___dsDrawObject(&object_obj_post4_post4[0]);
		}
	}
	else
	{
		SetObjectTexture();
		___dsDrawObject(&object_obj_post1_post1[0]);
	}
	njPopMatrix(1);
	npSetZCompare();
}

// FUNCTION: SADX 0x00821120
void ObjectPost1(struct task *pTask)
{
	pTask->twp->counter.l = 0;
	pTask->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	pTask->exec = Normal;
	pTask->disp = Normal;
}

// FUNCTION: SADX 0x00821150
void ObjectPost4(struct task *pTask)
{
	pTask->twp->counter.l = 3;
	pTask->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	pTask->exec = Normal;
	pTask->disp = Normal;
}
