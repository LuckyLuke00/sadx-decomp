#include "decls.h"
static void FExec(struct task *tp);
static void FDisp(struct task *tp);
extern struct NJS_TEXLIST texlist_ChaoBlackmarketObj;
extern struct obj object_kinblo_lamp_lamp[1];
extern struct NJS_MOTION motion_kinblo_lamp[1];
void FUN_004a7cb0(struct obj *param_1, struct NJS_MOTION *param_2, float param_3);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x0046e4d0
static void FDisp(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	___njSetTexture(&texlist_ChaoBlackmarketObj);
	njPushMatrixEx();
	FUN_0067d830((float *)0, -2.4f, 3.4f, -9.0f);
	FUN_004a7cb0((struct obj *)&object_kinblo_lamp_lamp, (struct NJS_MOTION *)&motion_kinblo_lamp, *(float *)((char *)var1 + 0x2c));
	njPopMatrixEx();
}

// FUNCTION: SADX 0x0046e530
static void FExec(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (var1->mode == 0)
	{
		tp->disp = FDisp;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->mode = 1;
	}
	var1->scl.x = var1->scl.x + 0.699999988079071;
	if (var1->scl.x > 4.0f)
	{
		var1->scl.x = 0.0f;
	}
	tp->disp(tp);
}

// FUNCTION: SADX 0x0046e580
struct task *ALO_BlackmarketLampCreate(struct task *parent_tp)
{
	return CreateChildTask(2, FExec, parent_tp);
}
