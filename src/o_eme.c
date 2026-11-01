#include "decls.h"
void DisplayEmeKiran(struct task *tp);
extern void *DAT_05a8167c;

// FUNCTION: SADX 0x005ba3f0
void ObjectEmeraldTriangleDisplay(struct NJS_POINT3 *pos)
{
	njPushMatrix(0);
	njTranslateV(0, pos);
	late_DrawPolygon3D((struct NJS_POINT3COL *)&tridai, 3, 0x20, 1);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005ba430
void ObjectEmeraldP(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckEditMode() == 0)
	{
		if ((local_8->ang.x & 0xf) == 0)
		{
			if (Knuckles_KakeraGame_Set_CheckEme(local_8->ang.z, &local_8->pos) == 0)
			{
				DeadOut(tp);
				return;
			}
		}
		else
		{
			Knuckles_KakeraGame_Set_ContPos(local_8->ang.z, &local_8->pos);
			DeadOut(tp);
			return;
		}
	}
	local_8->counter.ptr = &DAT_05a8167c;
	tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
	tp->exec = ObjectEmeraldPRegular;
}

// FUNCTION: SADX 0x005bac00
void DisplayEmeKiran(struct task *tp)
{
	struct taskwk *local_8g;
	int local_cg;

	local_8g = tp->twp;
	tp->disp = DisplayEmeKiran;
	if (ChkPause() == 0)
	{
		local_8g->counter.f += 1.0666667222976685;
	}
	if (local_8g->counter.f >= 4.0)
	{
		FreeTask(tp);
		return;
	}
	if (DAT_05b9d838 == 0)
	{
		SetMaterial(0.5f, 1.0f, 1.0f, 1.0f);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 10);
		SetRegularTexture();
		njPushMatrix(0);
		njTranslateV(0, &local_8g->pos);
		FUN_0067d2d0(0, local_8g->scl.x, local_8g->scl.x, local_8g->scl.x);
		local_cg = (unsigned int)local_8g->counter.f;
		late_DrawSprite3D(&sprite_eme_kiran, local_cg, 0x32, 4);
		njPopMatrix(1);
		ResetMaterial();
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
	}
	if (ChkPause() == 0)
	{
		CheckRangeOut(tp);
	}
}

// FUNCTION: SADX 0x005bad70
void CallObjectEmeraldDisplay(struct task *tp)
{
	ObjectEmeraldDisplay(&tp->twp->pos, &tp->twp->ang.y);
}
