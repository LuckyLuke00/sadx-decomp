#include "decls.h"
void FUN_00893670(struct task *param_1);

// FUNCTION: SADX 0x00893620
void DrawAmyDrum(struct taskwk *twp)
{
	if (!DAT_05b9d838)
	{
		SetObjectTexture();
		ResetMaterial();
		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		ds_DrawObjectClip((struct obj *)&object_dramcan_can_can, 1);
		njPopMatrix(1);
		ResetMaterial();
	}
}

// FUNCTION: SADX 0x008936d0
void ObjectFinalEggAmyDrum(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = FUN_00893670;
			if (FUN_004c39c0(tp) == 0)
			{
				CCL_Init(tp, cinfo_drum, 1, 4);
			}
			var1->mode = 1;
		}
		DrawAmyDrum(var1);
		if (FUN_004c39c0(tp) == 0)
		{
			EntryColliList(var1);
		}
	}
}
