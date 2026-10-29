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
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(NULL, *(unsigned short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
	}
	if (*(int *)((char *)var1 + 8) != 0)
	{
		if (*(int *)((char *)var1 + 8) == 3)
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
