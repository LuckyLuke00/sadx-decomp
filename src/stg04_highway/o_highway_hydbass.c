#include "decls.h"

// GLOBAL: SADX 0x03e71b54
static struct CCL_INFO object_c_info[1];

static void Norm(struct task *tp);
static void Draw(struct task *tp);

// FUNCTION: SADX 0x0081fcb0
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
		njPopMatrix(1);
	}
	else
	{
		___dsDrawObject(object_ss_hyd_hyd);
		njPopMatrix(1);
	}
}

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

// STUB: SADX 0x00820060
static void Norm(struct task *tp)
{
}

// FUNCTION: SADX 0x008201a0
void ObjectHighwayHydbass(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		var1->counter.ptr = (void *)&object_ss_hyd_hyd[0];
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_c_info[0], 1, 4);
			SET_COLLI_RANGE(var1->cwp, 11.0f);
		}
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Draw;
		tp->exec = Norm;
	}
}
