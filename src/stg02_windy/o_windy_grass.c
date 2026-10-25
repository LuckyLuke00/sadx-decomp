#include "decls.h"
static void Draw(struct task *tp);

// STUB: SADX 0x00808eb0
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (*(int *)&var1->ang.z)
	{
		njRotateZ(0, *(unsigned short *)&var1->ang.z);
	}
	if (var1->ang.x)
	{
		njRotateX(0, var1->ang.x);
	}
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(object_wvobj_busshu_busshu, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00808f60
void ObjectWindyGrass(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->disp = Draw;
			var1->mode = 1;
			break;
		case 1:
			Draw(tp);
			return;
		}
	}
}
