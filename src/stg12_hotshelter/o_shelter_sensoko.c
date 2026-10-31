#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x008b3f90
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	ds_DrawObjectClip((struct obj *)&object_sen_sensoko_before_sensoko_before, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x008b41e0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b4310
void ObjShelterSensoko(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->wtimer = 0;
	var1->mode = 0;
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = ExplosionRockDestructor;
}
