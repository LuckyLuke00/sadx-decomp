#include "decls.h"

// GLOBAL: SADX 0x0480c960
static struct NJS_MODEL *model_name[4];

static void Normal(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x008806c0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0x22);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)var1->ang.z);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		njScaleV(NULL, &var1->scl);
		DAT_05b3df40 = -37952.0f;
		late_DrawModelClip(model_name[var1->mode], 4, FUN_004a1e90((float *)&var1->scl));
		DAT_05b3df40 = 0.0f;
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00880790
static void Normal(struct task *tp)
{
}

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
