#include "decls.h"
static void Draw(struct task *tp);

#pragma optimize("", off)
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
		njRotateY(0, (Uint16)var1->ang.y);
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
#pragma optimize("", on)

// FUNCTION: SADX 0x0081ff60
void Hit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_POINT3 velo;
	if (var1->mode != 1)
	{
		LoopTaskC(tp);
	}
	velo.x = 0.0f;
	velo.y = 1.0f;
	velo.z = 0.0f;
	CreateWater(&var1->pos, &velo, 0.2f);
	Draw(tp);
	dsPlay_timer_v(0x79, (int)var1, 1, 0, 2, var1->pos.x, var1->pos.y, var1->pos.z);
}
