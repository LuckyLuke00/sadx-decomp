#include "decls.h"
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

// STUB: SADX 0x005bac00
void DisplayEmeKiran(struct task *tp)
{
}

// FUNCTION: SADX 0x005bad70
void CallObjectEmeraldDisplay(struct task *tp)
{
	ObjectEmeraldDisplay(&tp->twp->pos, &tp->twp->ang.y);
}
