#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_ssobj_shop1solt_shop1solt[1];

// FUNCTION: SADX 0x0068d0d0
void dispSSShop1Solt(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		SetObjectTexture();
		ds_DrawObjectClip((struct obj *)var1->counter.l, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0068d160
void ObjectSSShop1Solt(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp))
		{
			if (var1->counter.l == 0)
			{
				var1->counter.l = (long)&object_ssobj_shop1solt_shop1solt;
			}
			dispSSShop1Solt(tp);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			var1->counter.l = (long)&object_ssobj_shop1solt_shop1solt;
			tp->dest = destChaos7Float;
			tp->disp = dispSSShop1Solt;
			break;
		case 1:
			dispSSShop1Solt(tp);
			return;
		}
	}
}
