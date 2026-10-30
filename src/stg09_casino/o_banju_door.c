#include "decls.h"

// GLOBAL: SADX 0x0480c808
static struct CCL_INFO object_c_info[1];

static void Normal(struct task *tp);
static void Disp(struct task *tp);
extern int DAT_05b9d838;
extern struct NJS_MODEL model_card_doa_a_doa_a[];

// FUNCTION: SADX 0x0087f660
static void Disp(struct task *tp)
{
	struct taskwk *var1;

	if (DAT_05b9d838 == 0)
	{
		var1 = tp->twp;
		SetObjectTexture2(0x22);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		ds_DrawModelClip(model_card_doa_a_doa_a, 1.0f);
		njPopMatrix(1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0087f6d0
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0087f770
void ObjectBanjuDoor(struct task *tp)
{
	DAT_060dbcb0 &= 0xffffbfff;
	CCL_Init(tp, (struct CCL_INFO *)&object_c_info, 1, 4);
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
