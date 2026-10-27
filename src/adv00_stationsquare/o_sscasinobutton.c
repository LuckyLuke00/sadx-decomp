#include "decls.h"
extern struct NJS_MODEL *DAT_01cd8c58;
extern struct obj *DAT_01cd8c80;

// FUNCTION: SADX 0x00688630
void Disp(struct task *tp)
{
	struct taskwk *var1;
	struct obj *var2;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_ss_casino);
		SaveConstantAttr();
		if (var1->smode == 0)
		{
			OnConstantAttr(0, 0x2000000);
			OffConstantAttr(0x2000000, 0);
		}
		else
		{
			OnConstantAttr(0x2000000, 0);
			OffConstantAttr(0, 0x2000000);
		}
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		ds_DrawModelClip(DAT_01cd8c58, 1.0f);
		var2 = DAT_01cd8c80;
		FUN_0067d830(NULL, 0.0f, 0.0f, *(float *)((char *)var1 + 8));
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x1c));
		}
		ds_DrawModelClip(var2->model, 1.0f);
		njPopMatrix(1);
		LoadConstantAttr();
	}
}
