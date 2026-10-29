#include "decls.h"
static void DispATask(struct task *tp);
extern struct obj object_lightdw_daiv_daiv[];
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008abd90
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawObjectClipEx(object_lightdw_daiv_daiv, 4, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008abe00
void ObjShelterLight3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 250000.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			switch (var1->mode)
			{
			case 0:
				tp->disp = DispATask;
				tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
				tp->twp->mode = 1;
				break;
			case 1:
				DispATask(tp);
				break;
			}
		}
		else
		{
			switch (var1->mode)
			{
			case 1:
				DebPrintf(0x110010, "-> ROTATE X");
				DebPrintf(0x110011, "-> ROTATE Y");
				DebPrintf(0x110012, "-> ROTATE Z");
				DispATask(tp);
				break;
			case 0:
				tp->disp = DispATask;
				tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
				tp->twp->mode = 1;
				break;
			}
		}
	}
}
