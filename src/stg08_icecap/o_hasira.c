#include "decls.h"
static void Normal2(struct task *tp);
static void Exit(struct task *tp);

// GLOBAL: SADX 0x045dab08
static struct CCL_INFO object_c_info[5];

extern int DAT_05b9d838;
extern struct NJS_MODEL model__obj_hasira_c_obj_hasira_c[];

// FUNCTION: SADX 0x008665e0
static void Exit(struct task *tp)
{
	if (tp->twp->mode == 2)
	{
		struct obj *var1;
		var1 = (struct obj *)tp->twp->counter.ptr;
		WithdrawCollisionEntry(tp, var1);
		ReleaseMobileLandObject(var1);
	}
}

// FUNCTION: SADX 0x00866a50
void Normal1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (DAT_05b9d838 == 0)
		{
			if (FUN_004c39c0(tp) == 0)
			{
				EntryColliList(var1);
				ObjectSetupInput(var1, (struct motionwk *)0);
			}
			SetObjectTexture();
			njPushMatrix(NULL);
			njTranslateV(NULL, &var1->pos);
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x14) != 0)
			{
				njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
			}
			if (*(int *)((char *)var1 + 0x18) != 0)
			{
				njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
			}
			late_DrawModelClipMesh((struct NJS_MODEL *)&model__obj_hasira_c_obj_hasira_c, 0, 1.0f);
			njPopMatrix(1);
		}
	}
}

#pragma optimize("", off)
// STUB: SADX 0x00866b20
static void Normal2(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00866c20
void ObjectHasira1b(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->scl.x = 3.0f;
	var1->scl.y = 0.0f;
	var1->flag &= 0xfcff;
	var1->mode = 0;
	var1->timer.l = 0;
	CCL_Init(tp, object_c_info, 1, 4);
	tp->exec = Normal0;
	tp->disp = Normal0;
	tp->dest = Exit;
}


// FUNCTION: SADX 0x00866cb0
void ObjectHasira10c(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = SetModelCollision(&object__obj_hasira10c_obj_hasira10c[0], tp, 0x40000001);

	var1->counter.ptr = var2;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	CCL_Init(tp, &object_c_info[2], 3, 4);
	*(unsigned char *)((char *)var1 + 0) = 2;
	tp->exec = Normal2;
	tp->disp = Normal2;
	tp->dest = Exit;
}
