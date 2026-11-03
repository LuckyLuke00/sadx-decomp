#include "decls.h"

// STUB: SADX 0x0084e020
void ObjectSkydeck_eff_hahen1_End(struct task *tp)
{
}

// FUNCTION: SADX 0x0084e050
void ObjectSkydeck_eff_hahen1_Draw(struct task *tp)
{
	struct taskwk *var1;
	int var2;
	int *var3;
	int var4;
	int var5;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 2250100.0f) == 0)
	{
		var3 = *(int **)((char *)var1 + 0x10);
		var2 = 0;
		if (*var3 > 0)
		{
			var5 = 0;
			do
			{
				var4 = var3[3] + var5;
				___njSetTexture(&texlist_obj_skydeck);
				njPushMatrix(NULL);
				njTranslateV(NULL, (NJS_VECTOR *)var4);
				if (*(int *)(var4 + 0x18) != 0)
				{
					njRotateX(NULL, *(unsigned short *)(var4 + 0x18));
				}
				if (*(int *)(var4 + 0x20) != 0)
				{
					njRotateZ(NULL, *(unsigned short *)(var4 + 0x20));
				}
				ds_DrawObjectClip((struct obj *)*(int *)((char *)var1 + 8), 1.0f);
				njPopMatrix(1);
				var3 = *(int **)((char *)var1 + 0x10);
				var2 = var2 + 1;
				var5 = var5 + 0x30;
			}
			while (var2 < *var3);
		}
	}
}

// FUNCTION: SADX 0x0084e210
void ObjectSkydeck_eff_hahen1(struct task *tp)
{
	struct taskwk *var1;

	if (CheckRangeOutWithR(tp, 2250100.0f) == 0)
	{
		var1 = tp->twp;
		tp->disp = ObjectSkydeck_eff_hahen1_Draw;
		tp->exec = ObjectSkydeck_eff_hahen1_Exec;
		tp->dest = ObjectSkydeck_eff_hahen1_End;
		var1->wtimer = 0;
		var1->mode = 0;
	}
}
