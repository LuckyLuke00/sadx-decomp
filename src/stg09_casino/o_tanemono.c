#include "decls.h"

// GLOBAL: SADX 0x0480c908
static struct NJS_MODEL *model_name[22];

static void Normal(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x008805b0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0x22);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (var1->ang.y != 0)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		late_DrawModel(model_name[(int)(char)var1->mode], 4);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00880650
static void Normal(struct task *tp)
{
}

// FUNCTION: SADX 0x00880690
void ObjectTanemono(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 0;
	var1->btimer = 0;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
