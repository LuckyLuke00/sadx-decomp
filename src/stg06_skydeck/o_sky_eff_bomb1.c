#include "decls.h"
extern struct CCL_INFO object_eff_smallbomb1_info[];

// STUB: SADX 0x0084bb10
void EffBombThrowPlayer(struct taskwk *twp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0084bd50
void ObjectSkydeck_eff_bomb1_Init(struct task *tp)
{
}
#pragma optimize("", on)

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
