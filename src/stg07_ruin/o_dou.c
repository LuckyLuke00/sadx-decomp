#include "decls.h"
static void Normal(struct task *pTask);

// FUNCTION: SADX 0x008525c0
static void Normal(struct task *pTask)
{
	struct taskwk *var1;
	var1 = pTask->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00852610
void ObjectDou1(struct task *pTask)
{
	pTask->twp->mode = 0;
	pTask->exec = Normal;
	pTask->disp = Normal;
	pTask->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00852630
void ObjectDou2(struct task *pTask)
{
	pTask->twp->mode = 1;
	pTask->exec = Normal;
	pTask->disp = Normal;
	pTask->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
