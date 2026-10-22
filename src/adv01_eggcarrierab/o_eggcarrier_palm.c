#include "decls.h"
static void DrawGiantPalm(struct taskwk *twp);

// FUNCTION: SADX 0x00695510
static void DrawGiantPalm(struct taskwk *twp)
{
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		if (twp->ang.y != 0)
		{
			njRotateY(0, (unsigned short)twp->ang.y);
		}
		late_DrawObjectClipEx(DAT_060eea88[0x2d], 1, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00695570
void GiantPalmDisplayer(struct task *tp)
{
	DrawGiantPalm(tp->twp);
}

// FUNCTION: SADX 0x00695580
void ObjectECGiantPalm(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			if (FUN_004c39c0(tp) == 0)
			{
				CCL_Init(tp, cinfo_palm, 1, 4);
			}
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = GiantPalmDisplayer;
			var1->mode = 1;
		}
		DrawGiantPalm(var1);
		if (FUN_004c39c0(tp) == 0)
		{
			EntryColliList(var1);
		}
	}
}
