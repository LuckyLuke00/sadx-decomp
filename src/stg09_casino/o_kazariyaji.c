#include "decls.h"
static void Normal(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x008806c0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0x22);
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
		}
		njScaleV((float *)0, &var1->scl);
		DAT_05b3df40 = -37952.0f;
		late_DrawModelClip(model_name[*(signed char *)((char *)var1)], 4, FUN_004a1e90((float *)&var1->scl));
		DAT_05b3df40 = 0.0f;
		njPopMatrix(1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x00880790
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008807d0
void ObjectKazariYaji(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 0;
	var1->btimer = 0;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
