#include "decls.h"
static void Normal(struct task *tp);
extern unsigned char DAT_048093da;
extern float pos_table[5][3];
extern struct NJS_MOTION motion_card_obj_ideacp[1];
static void Disp(struct task *tp);

// FUNCTION: SADX 0x00882450
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0 && DAT_048093da <= 4)
	{
		SetObjectTexture2(0x22);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		FUN_004a8800((struct obj *)*(int *)((float *)&pos_table[4][2] + DAT_048093da), (struct NJS_MOTION *)&motion_card_obj_ideacp, var1->timer.f, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00882510
static void Normal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = var1->timer.f + 0.10000000149011612;
	if (var1->timer.f >= 15.0)
	{
		var1->timer.f = 0.0;
	}
	Disp(tp);
}

// FUNCTION: SADX 0x00882550
void ObjectIdeacap(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = 0.0f;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
