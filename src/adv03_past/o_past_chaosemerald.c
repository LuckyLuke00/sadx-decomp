#include "decls.h"
extern struct obj *DAT_060b97f4[4];

// FUNCTION: SADX 0x006bf900
void EmeraldDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y + var1->value.f, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	late_DrawObjectClipMesh(DAT_060b97f4[var1->smode], 1, 1.0f);
	njPopMatrix(1);
}
