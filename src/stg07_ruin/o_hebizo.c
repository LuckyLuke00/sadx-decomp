#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_MODEL model_lwobj_snake02_snake02[1];

// FUNCTION: SADX 0x00856d80
void dispNormal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		SetObjectTexture();
		ds_DrawModelClip(&model_lwobj_snake02_snake02[0], 1.0f);
		njPopMatrix(1);
	}
}
