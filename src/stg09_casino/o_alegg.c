#include "decls.h"
static void Normal(struct task *tp);
extern float DAT_05b3df40;
extern struct taskwk *DAT_05b42a7c;
extern int DAT_05b9d838;
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0087f7b0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0x22);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (DAT_05b42a7c->ang.y != 0)
		{
			njRotateY(0, (unsigned short)DAT_05b42a7c->ang.y);
		}
		DAT_05b3df40 = 250.0f;
		late_ActionEx((struct NJS_ACTION *)&action_alegg_body_o, var1->counter.f, 4, 1.0f);
		DAT_05b3df40 = 0.0f;
		njPopMatrix(1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0087f840
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0087f910
void ObjectSitaAlEgg(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->btimer = 0;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x0087f940
void ObjectUeAlEgg(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->btimer = 1;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
