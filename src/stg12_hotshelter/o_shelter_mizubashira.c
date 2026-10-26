#include "decls.h"
extern struct NJS_TEXLIST texlist_shelter_column;
extern struct obj object_mizubasira_pasya_sita_pasya_sita[];
extern int DAT_05b9d838;
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// STUB: SADX 0x008b3430
void Pasya0Disp(struct task *tp)
{
}

// FUNCTION: SADX 0x008b34e0
void Pasya1Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_shelter_column);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	FUN_0067d2d0(0, var1->scl.x, 1.2f, var1->scl.x);
	ds_DrawObjectClip(object_mizubasira_pasya_sita_pasya_sita, var1->scl.x > 1.2f ? var1->scl.x : 1.2f);
	njPopMatrix(1);
}

// STUB: SADX 0x008b3590
void Pasya0Exec(struct task *tp)
{
}

// STUB: SADX 0x008b3670
void Pasya1Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008b3740
void Pasya0Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y -= 2.0;
	var1->btimer = 0;
	var1->wtimer = 0;
	tp->exec = Pasya0Exec;
	tp->disp = Pasya0Disp;
}

// FUNCTION: SADX 0x008b3770
void Pasya1Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y -= 80.5f;
	var1->btimer = 0;
	var1->wtimer = 0;
	var1->counter.f = 0.0f;
	tp->exec = Pasya1Exec;
	tp->disp = Pasya1Disp;
}
