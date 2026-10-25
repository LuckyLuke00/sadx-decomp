#include "decls.h"
static void Draw(struct task *tp);

// STUB: SADX 0x0081fcb0
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	if (var1->mode == 2)
	{
		___dsDrawModel(model_ss_hyd_hydbase);
		((void (*)())njPopMatrix)();
	}
	else
	{
		___dsDrawObject(object_ss_hyd_hyd);
		((void (*)())njPopMatrix)();
	}
}

// FUNCTION: SADX 0x0081ff60
void Hit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_POINT3 local_14;
	if (var1->mode != 1)
	{
		LoopTaskC(tp);
	}
	local_14.x = 0.0f;
	local_14.y = 1.0f;
	local_14.z = 0.0f;
	CreateWater(&var1->pos, &local_14, 0.2f);
	Draw(tp);
	dsPlay_timer_v(0x79, (int)var1, 1, 0, 2, var1->pos.x, var1->pos.y, var1->pos.z);
}
