#include "decls.h"
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void ghSetPvrTexMaterial(unsigned long color);
void ghDrawPvrSprite(short *param_1, int param_2, float param_3, float param_4, float param_5, float param_6, float param_7);
extern struct NJS_TEXLIST texlist_ava_back;
extern float ScreenRaitoX;
extern float ScreenRaitoY;

// FUNCTION: SADX 0x005a4120
void DrawSkyBg(float z)
{
	___njSetTexture(&texlist_ava_back);
	ghSetPvrTexMaterial(0xffffffff);
	ghDrawPvrSprite((short *)0x26314d4, 0, 0.0, 0.0, z, ScreenRaitoX, ScreenRaitoY);
	return;
}
