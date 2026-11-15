#include "decls.h"
extern struct NJS_ACTION action_wvobj_tree[1];
static void Draw(struct task *tp);

// FUNCTION: SADX 0x00809e00
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_MOTION *var2 = action_wvobj_tree[0].motion;
	if (var1->counter.f >= (float)(unsigned int)var2->nbFrame)
	{
		var1->counter.f = 0.0f;
	}
	SetObjectTexture();
	njPushMatrix(NULL);
	FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
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
	late_ActionClipEx((struct NJS_ACTION *)&action_wvobj_tree, var1->counter.f, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00809ed0
void ObjectWindyTreeM(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = Draw;
			var1->mode = 1;
			break;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				var1->counter.f += var1->scl.x;
			}
			if (FUN_004c39c0(tp) != 0)
			{
				njPrintC(0x110013, "<- MOTION_SPEED");
			}
			Draw(tp);
			return;
		}
	}
}
