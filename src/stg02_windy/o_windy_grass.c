#include "decls.h"
static void Draw(struct task *tp);

// FUNCTION: SADX 0x00808eb0
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		ds_DrawObjectClip((struct obj *)&object_wvobj_busshu_busshu, 1.0f);
		njPopMatrix(1);
	}
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
