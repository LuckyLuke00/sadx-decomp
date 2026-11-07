#include "decls.h"
extern struct obj object_c7_dead02_dead02[1];
extern struct NJS_ACTION action_c7_dead02[1];
extern struct obj object_c7_dead03_dead03[];
extern struct NJS_ACTION action_c7_dead03[];
extern struct obj object_c7_dead01_dead01[];
extern struct NJS_ACTION action_c7_dead01[1];
extern struct NJS_TEXLIST texlist_chaos7_0dead_ptchg;
static void Normal2(struct task *tp);
static void Normal1(struct task *tp);

// FUNCTION: SADX 0x00700f90
void Display1(struct task *tp)
{
	struct NJS_ARGB argb;
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838)
	{
		return;
	}
	object_c7_dead01_dead01[0].model->mats->attr_texId = (int)var1->timer.b[1];
	argb.a = var1->value.f;
	argb.b = 1.0f;
	argb.g = 1.0f;
	argb.r = 1.0f;
	___njFogDisable();
	SaveControl3D();
	OnControl3D(0x10);
	___njSetConstantMaterial(&argb);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	FUN_0067d2d0(0, 1.0f, 1.0f, 1.0f);
	___njSetTexture(&texlist_chaos7_0dead_ptchg);
	DAT_05b3df40 = 1000.0f;
	late_ActionMS((struct NJS_ACTION *)&action_c7_dead01, var1->counter.f, 4);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
	LoadControl3D();
	___njFogEnable();
}

// STUB: SADX 0x00701080
static void Normal1(struct task *tp)
{
}

// FUNCTION: SADX 0x00701110
void Chaos7DeadEffect1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->value.f = 0.0f;
	var1->counter.f = 0.0f;
	tp->exec = Normal1;
	tp->disp = Display1;
}

// FUNCTION: SADX 0x00701130
void Display2(struct task *tp)
{
	struct taskwk *var1;
	struct NJS_ARGB argb;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		object_c7_dead02_dead02[0].model->mats->attr_texId = var1->timer.b[1] + 8;
		argb.a = var1->value.f;
		argb.b = 1.0f;
		argb.g = 1.0f;
		argb.r = 1.0f;
		___njFogDisable();
		SaveControl3D();
		OnControl3D(0x10);
		___njSetConstantMaterial(&argb);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		FUN_0067d2d0(NULL, 1.0f, 1.0f, 1.0f);
		___njSetTexture(&texlist_chaos7_0dead_ptchg);
		DAT_05b3df40 = 1000.0f;
		late_ActionMS((struct NJS_ACTION *)&action_c7_dead02, var1->counter.f, 4);
		DAT_05b3df40 = 0.0f;
		njPopMatrix(1);
		LoadControl3D();
		___njFogEnable();
	}
}

// STUB: SADX 0x00701220
static void Normal2(struct task *tp)
{
}

// FUNCTION: SADX 0x007012b0
void Chaos7DeadEffect2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->value.f = 0.0f;
	var1->counter.f = 0.0f;
	tp->exec = Normal2;
	tp->disp = Display2;
}

// FUNCTION: SADX 0x007012d0
void Display3(struct task *tp)
{
	struct taskwk *var1;
	struct NJS_ARGB argb;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		object_c7_dead03_dead03[0].model->mats->attr_texId = var1->timer.b[1] + 0x10;
		argb.a = var1->value.f;
		argb.b = 1.0f;
		argb.g = 1.0f;
		argb.r = 1.0f;
		___njFogDisable();
		SaveControl3D();
		OnControl3D(0x10);
		___njSetConstantMaterial(&argb);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		FUN_0067d2d0(NULL, 1.0f, 1.0f, 1.0f);
		___njSetTexture(&texlist_chaos7_0dead_ptchg);
		DAT_05b3df40 = 1000.0f;
		late_ActionMS((struct NJS_ACTION *)&action_c7_dead03, var1->counter.f, 4);
		DAT_05b3df40 = 0.0f;
		njPopMatrix(1);
		LoadControl3D();
		___njFogEnable();
	}
}

// FUNCTION: SADX 0x007013d0
void Normal3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->counter.f < 8.0f)
	{
		var1->value.f = var1->counter.f * 0.125f;
	}
	else if (var1->counter.f > 20.0f)
	{
		var1->value.f = (31.0f - var1->counter.f) / 11.0f;
	}
	else
	{
		var1->value.f = 1.0f;
	}
	var1->timer.b[0]++;
	if (var1->timer.b[0] >= 2)
	{
		var1->timer.b[1]++;
		var1->timer.b[0] = 0;
		if (var1->timer.b[1] >= 8)
		{
			var1->timer.b[1] = 0;
		}
	}
	var1->counter.f += 0.25833332f;
	if (var1->counter.f >= 31.0f)
	{
		var1->timer.b[2]--;
		if (var1->timer.b[2] > 0)
		{
			var1->counter.f = 0.0f;
		}
		else
		{
			FreeTask(tp);
			return;
		}
	}
	var1->ang.y += 0x100;
	Display3(tp);
}

// FUNCTION: SADX 0x00701480
void Chaos7DeadEffect3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	tp->exec = Normal3;
	tp->disp = Display3;
	var1->value.f = 0.0f;
	var1->counter.f = 0.0f;
	var1->timer.b[2] = 2;
}
