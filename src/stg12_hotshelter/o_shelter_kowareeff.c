#include "decls.h"
static void Disp(struct task *tp);
static void Exec(struct task *tp);

// FUNCTION: SADX 0x008b6cd0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_shelter_column);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	FUN_0067d830(0, 0.0f, var1->value.f, 0.0f);
	FUN_0067d2d0(0, var1->scl.x, 1.0f, var1->scl.x);
	SetMaterial(var1->timer.f, 0.0f, 0.0f, 0.0f);
	late_ActionClip(action_kowaresuisou_mizu_ef, var1->counter.f, 0, var1->scl.x > 1.0f ? var1->scl.x : 1.0f);
	ResetMaterial();
	njPopMatrix(1);
}

// STUB: SADX 0x008b6da0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b6ef0
void ObjShelterKowareeff(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->scl.x = 1.0;
	var1->counter.f = 0.0;
	var1->btimer = 0;
	var1->timer.f = 0.0;
	var1->wtimer = 0;
	var1->value.f = 40.0f;
	var1->mode = 0;
	var1->scl.z = -1.0;
	tp->exec = Exec;
	tp->disp = Disp;
}
