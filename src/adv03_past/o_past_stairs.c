#include "decls.h"
extern struct taskwk *DAT_05b42a7c;
extern struct obj *DAT_060eeaa4;
void FUN_007d21b0(...);

// FUNCTION: SADX 0x006c0800
void PyramidStairsDisplayer(struct task *tp)
{
	struct taskwk *var1;
	float var2;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, var1->ang.y);
	}
	var2 = njSqrt((var1->pos.x - DAT_05b42a7c->pos.x) * (var1->pos.x - DAT_05b42a7c->pos.x) + (var1->pos.y - DAT_05b42a7c->pos.y) * (var1->pos.y - DAT_05b42a7c->pos.y) + (var1->pos.z - DAT_05b42a7c->pos.z) * (var1->pos.z - DAT_05b42a7c->pos.z));
	if (var2 < 400.0)
	{
		late_DrawObjectClipEx((struct obj *)(*(void **)((char *)DAT_060eeaa4 + 0x54)), 1, 1.0);
		njPopMatrix(1);
	}
	else
	{
		late_DrawObjectClipEx((struct obj *)(*(void **)((char *)DAT_060eeaa4 + 0x58)), 1, 1.0);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x006c08d0
void BigStairsDisplayer(struct task *tp)
{
	struct taskwk *var1;
	float var2;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, var1->ang.y);
	}
	var2 = njSqrt((var1->pos.x - DAT_05b42a7c->pos.x) * (var1->pos.x - DAT_05b42a7c->pos.x) + (var1->pos.y - DAT_05b42a7c->pos.y) * (var1->pos.y - DAT_05b42a7c->pos.y) + (var1->pos.z - DAT_05b42a7c->pos.z) * (var1->pos.z - DAT_05b42a7c->pos.z));
	if (var2 < 400.0f)
	{
		late_DrawObjectClipEx(*(struct obj **)((char *)DAT_060eeaa4 + 0x50), 1, 1.0f);
	}
	else
	{
		late_DrawObjectClipEx(*(struct obj **)((char *)DAT_060eeaa4 + 0x4c), 1, 1.0f);
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006c09a0
void ObjectPastPyramidStairs(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->disp = PyramidStairsDisplayer;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->twp->mode = 1;
	}
	PyramidStairsDisplayer(tp);
}

// FUNCTION: SADX 0x006c09d0
void ObjectPastBigStairs(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->disp = BigStairsDisplayer;
		tp->dest = (void (*)(struct task *))FUN_007d21b0;
		tp->twp->mode = 1;
	}
	BigStairsDisplayer(tp);
}
