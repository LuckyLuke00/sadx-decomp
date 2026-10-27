#include "decls.h"
extern short DAT_026314d4[25];
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void ghSetPvrTexMaterial(unsigned long color);
void ghDrawPvrSpriteS(short *pvrspr, int flag, float x, float y, float z, float sx, float sy);
extern struct NJS_TEXLIST texlist_ava_back;
extern float ScreenRaitoX;
extern float ScreenRaitoY;

// FUNCTION: SADX 0x005a4120
void DrawSkyBg(float z)
{
	___njSetTexture(&texlist_ava_back);
	ghSetPvrTexMaterial(0xffffffff);
	ghDrawPvrSpriteS(DAT_026314d4, 0, 0.0f, 0.0f, z, ScreenRaitoX, ScreenRaitoY);
}
