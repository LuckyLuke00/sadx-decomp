#include "decls.h"
extern struct NJS_ACTION action_kowaresuisou_hikari_sin[1];
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x008a5c70
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		late_ActionClip((struct NJS_ACTION *)&action_kowaresuisou_hikari_sin, var1->counter.f, 4, 1.0f);
		njPopMatrix(1);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x008a5ce0
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008a5d90
void ObjShelterBluelight(struct task *tp)
{
	tp->twp->counter.f = 0.0f;
	tp->exec = Exec;
	tp->disp = Disp;
}
