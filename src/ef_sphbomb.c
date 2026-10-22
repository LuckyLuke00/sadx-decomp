#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_MODEL model_expoly;
void late_DrawModel(struct NJS_MODEL *mdl, int flgs);

// STUB: SADX 0x006103c0
void SphericalExplosionUV(long v0)
{
}

// STUB: SADX 0x00610480
void SphericalExplosionPos(float rate)
{
}

// STUB: SADX 0x006105b0
void SphericalExplosionAlpha(float a)
{
}

// FUNCTION: SADX 0x00610620
void SphericalExplosionDraw()
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	late_DrawModel(&model_expoly, 1);
}
