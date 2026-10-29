#include "decls.h"
extern struct obj object_hasigo_hasigo_hotsh_hasigo_hotsh[1];
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008a5ee0
void Hasigo_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.x)
	{
		njRotateX(0, (Uint16)var1->ang.x);
	}
	if (var1->ang.y + 0x8000)
	{
		njRotateY(0, (unsigned short)(var1->ang.y + 0x8000));
	}
	late_DrawModelClipMesh(object_hasigo_hasigo_hotsh_hasigo_hotsh[0].model, 1, 1.0f);
	njPopMatrix(1);
}
