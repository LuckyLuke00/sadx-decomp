#include "decls.h"
extern struct CCL_INFO object_eff_bomb1_info[1];
extern struct obj object_sky_h_bakuha01a_h_bakuha01a[1];
extern struct obj object_sky_h_bakuha02a_h_bakuha02a[1];
extern struct obj object_sky_h_bakuha03a_h_bakuha03a[1];
extern struct obj object_sky_h_bakuha04a_h_bakuha04a[1];
extern struct obj object_sky_h_bakuha05a_h_bakuha05a[1];
extern struct CCL_INFO object_eff_smallbomb1_info[];

// STUB: SADX 0x0084bb10
void EffBombThrowPlayer(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x0084bd50
void ObjectSkydeck_eff_bomb1_Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_eff_bomb1_info, 1, 4);
	}
	tp->disp = ObjectSkydeck_eff_bomb1_Draw;
	tp->exec = ObjectSkydeck_eff_bomb1_Exec;
	var1->value.f = 1.0f;
	var1->mode = 1;
	var1->counter.f = 0.0f;
	var1->wtimer = 0;
	{
		struct NJS_MATERIAL *var2;
		unsigned long var3;
		var2 = object_sky_h_bakuha05a_h_bakuha05a[0].model->mats;
		var3 = var2[0].attrflags & 0x3efffff;
		var3 |= 0x84100000;
		var2[0].attrflags = var3;
		var2 = object_sky_h_bakuha01a_h_bakuha01a[0].model->mats;
		var3 = var2[0].attrflags & 0x3efffff;
		var3 |= 0x84100000;
		var2[0].attrflags = var3;
		var2 = object_sky_h_bakuha02a_h_bakuha02a[0].model->mats;
		var3 = var2[0].attrflags & 0x3efffff;
		var3 |= 0x84100000;
		var2[0].attrflags = var3;
		var2 = object_sky_h_bakuha03a_h_bakuha03a[0].model->mats;
		var3 = var2[0].attrflags & 0x3efffff;
		var3 |= 0x84100000;
		var2[0].attrflags = var3;
		var2 = object_sky_h_bakuha04a_h_bakuha04a[0].model->mats;
		var3 = var2[0].attrflags & 0x3efffff;
		var3 |= 0x84100000;
		var2[0].attrflags = var3;
	}
}

// FUNCTION: SADX 0x0084be30
void FUN_0084be30(struct task *param_1)
{
	struct taskwk *var1;

	if (CheckRangeOutWithR(param_1, 2250100.0f) == 0)
	{
		var1 = param_1->twp;
		if (FUN_004c39c0(param_1) == 0)
		{
			CCL_Init(param_1, &object_eff_smallbomb1_info[0], 1, 4);
		}
		param_1->exec = ObjectSkydeck_eff_smallbomb1_Exec;
		var1->value.f = 1.0f;
		var1->wtimer = 0;
		var1->counter.f = 0.0f;
		var1->mode = 1;
	}
}

// FUNCTION: SADX 0x0084be90
struct task *CreateEffSmallBomb1(struct NJS_POINT3 *pos, float scl)
{
	struct task *var1;
	struct taskwk *var2;
	var1 = CreateElementalTask(2, 3, (void (__cdecl *)(struct task *))FUN_0084be30);
	if (var1 != 0)
	{
		var2 = var1->twp;
		var2->pos = *pos;
		var2->timer.f = scl;
		return var1;
	}
	return 0;
}

// FUNCTION: SADX 0x0084bed0
void ObjectSkydeck_eff_bomb1(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 2250100.0f) == 0)
	{
		ObjectSkydeck_eff_bomb1_Init(tp);
	}
}

// STUB: SADX 0x0084bf00
struct task *CreateEffBomb2(struct NJS_POINT3 *pos, float scl, long angX, long angZ)
{
	return (struct task *)0;
}
