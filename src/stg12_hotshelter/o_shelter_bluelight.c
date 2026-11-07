#include "decls.h"
extern "C" double atan2(double v, double u);
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

// FUNCTION: SADX 0x008a5ce0
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		float var2 = var1->counter.f + 1.0f;
		var1->counter.f = var2;
		float var3 = (float)(unsigned int)(action_kowaresuisou_hikari_sin[0].motion->nbFrame - 1);
		if (var3 <= var2)
		{
			var1->counter.f = var2 - var3;
		}
		float var4 = DAT_05b42a7c->pos.x - var1->pos.x;
		float var5 = DAT_05b42a7c->pos.z - var1->pos.z;
		var1->ang.y = (int)(atan2(var4, var5) * 65536.0f / 6.283184);
		Disp(tp);
	}
}

// FUNCTION: SADX 0x008a5d90
void ObjShelterBluelight(struct task *tp)
{
	tp->twp->counter.f = 0.0f;
	tp->exec = Exec;
	tp->disp = Disp;
}
