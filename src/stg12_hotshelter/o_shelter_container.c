#include "decls.h"

// FUNCTION: SADX 0x008ab900
void HahenDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_MODEL *var2;

	if (DAT_05b9d838)
	{
		return;
	}
	var2 = (struct NJS_MODEL *)var1->value.ptr;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	ds_DrawModelClip((struct NJS_MODEL *)var2->normals, 1.0f);
	njPopMatrix(1);
}
