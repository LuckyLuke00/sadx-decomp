#include "decls.h"
extern struct NJS_MODEL DAT_05a862b0;

// FUNCTION: SADX 0x006b0700
void PASTDrawShadow(float radius)
{
	SetRegularTexture();
	FUN_0067d830(0, 0.0f, 0.6f, 0.0f);
	njPushMatrix(0);
	radius *= 0.25;
	FUN_0067d2d0(0, radius, radius, radius * 0.800000011920929);
	late_DrawShadowModel(&DAT_05a862b0, radius);
	njPopMatrix(1);
}
