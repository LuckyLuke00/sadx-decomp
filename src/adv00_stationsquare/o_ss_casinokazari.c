#include "decls.h"
extern struct obj object_casinoobj_builg_builg[1];

// STUB: SADX 0x006821d0
void SetMatAttribute(struct obj *op, unsigned long attr)
{
}

// STUB: SADX 0x00682220
void ResetMatAttribute(struct obj *op, unsigned long attr)
{
}

// FUNCTION: SADX 0x00682460
void DispDay(struct task *tp)
{
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_ss_casino);
		FUN_00422560(3);
		for (int var1 = 0; var1 < 3; var1++)
		{
			ds_DrawObjectClip(objs[var1], 1.0f);
		}
		npSetZCompare();
		ds_DrawObjectClip(&object_casinoobj_casinobuil_casinobuil[0], 1.0f);
		ds_DrawObjectClip(&object_casinoobj_builg_builg[0], 1.0f);
	}
}

// FUNCTION: SADX 0x00682740
void ExecDay(struct task *tp)
{
	DispDay(tp);
}
