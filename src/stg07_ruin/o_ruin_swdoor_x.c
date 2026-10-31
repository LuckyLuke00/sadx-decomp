#include "decls.h"
static void Disp(struct task *tp);

// GLOBAL: SADX 0x043ac484
static struct CCL_INFO c_info_door[1];

static void Exec(struct task *tp);
void ___njSetTexture(struct NJS_TEXLIST *texlist);
extern struct NJS_TEXLIST texlist_sw_panel;
extern struct obj object_lwobj_lwdoor_lwdoor[];
extern int DAT_05b9d838;
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void ds_DrawObjectClip(struct obj *obj, float clipScl);

// FUNCTION: SADX 0x00852650
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_sw_panel);
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y + var1->counter.f, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	if (var1->timer.f)
	{
		FUN_0067d830(0, 0.0f, 0.0f, var1->timer.f);
	}
	ds_DrawObjectClip(object_lwobj_lwdoor_lwdoor, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x00852710
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00852ae0
void ObjectRuinSwdoorX(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.f = 0.0f;
	var1->timer.f = 0.0f;
	var1->wtimer = 0;
	var1->mode = 0;
	var1->value.l = 0;
	var1->scl.x = -njCos(*(Angle *)((char *)var1 + 0x18));
	var1->scl.z = njSin(*(Angle *)((char *)var1 + 0x18));
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, &c_info_door[0], 1, 4);
	}
	tp->exec = Exec;
	tp->disp = Disp;
}
