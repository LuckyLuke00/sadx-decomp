#include "decls.h"
static void Normal(struct task *tp);
static void Hit(struct task *tp, int timer);
static void Draw(struct task *tp);
extern struct NJS_MODEL model_glass_cube_1_cube_1[];

// FUNCTION: SADX 0x008242c0
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	late_DrawModel((struct NJS_MODEL *)&model_glass_cube_1_cube_1, 4);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00824330
void DrawGlass(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_MODEL *var2 = (struct NJS_MODEL *)var1->timer.ptr;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	late_DrawModel((struct NJS_MODEL *)var2->normals, 4);
	njPopMatrix(1);
}

// STUB: SADX 0x008244f0
void GlassBroken(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00824590
static void Hit(struct task *tp, int timer)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008246e0
void ObjectHighwayGlassAct2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 2250000.0f))
	{
		return;
	}
	switch (var1->mode)
	{
	case 0:
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Draw;
		CCL_Init(tp, gls_colli, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 200.0f);
		var1->mode = 1;
		break;
	case 1:
		if (!FUN_004c39c0(tp))
		{
			if (var1->cwp->flag & 1)
			{
				var1->cwp->flag &= 0xfffe;
				var1->mode = 2;
				var1->btimer = 1;
				return;
			}
			EntryColliList(var1);
		}
		Draw(tp);
		break;
	case 2:
		Hit(tp, 1);
		break;
	case 3:
		DeadOut(tp);
	default:
		var1->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x008247c0
void Break(struct task *tp)
{
	Draw(tp);
	Hit(tp, 0x3c);
}

#pragma optimize("", off)
// STUB: SADX 0x008247e0
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008248b0
void ObjectHighwayGlass(struct task *tp)
{
	if (!CheckRangeOut(tp))
	{
		if (!FUN_004c39c0(tp))
		{
			CCL_Init(tp, glass_colli_info, 1, 4);
		}
		tp->exec = Normal;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Draw;
		Draw(tp);
	}
}
