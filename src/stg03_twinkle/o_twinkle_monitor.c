#include "decls.h"

// FUNCTION: SADX 0x00819950
void dispTPMonitor(struct task *tp)
{
	struct taskwk *var1;
	struct NJS_MODEL *var2;
	struct NJS_MODEL *var3;

	var1 = tp->twp;
	var2 = (struct NJS_MODEL *)var1->counter.ptr;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		njTranslateV(NULL, (struct NJS_POINT3 *)((char *)var2 + 8));
		ds_DrawModelClip((struct NJS_MODEL *)var2->normals, 1.0f);
		njPushMatrix(NULL);
		var3 = (struct NJS_MODEL *)(*(int *)((char *)var2 + 0x2c));
		njTranslateV(NULL, (struct NJS_POINT3 *)((char *)var3 + 8));
		if (var1->value.ptr != 0)
		{
			njRotateX(NULL, (unsigned short)var1->value.ptr);
		}
		ds_DrawModelClip((struct NJS_MODEL *)var3->normals, 1.0f);
		njPopMatrix(1);
		njPopMatrix(1);
	}
}
