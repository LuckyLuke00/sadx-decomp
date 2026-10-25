#include "decls.h"
extern struct NJS_TEXLIST DAT_060cf104;
extern float DAT_060cf0f8;
extern float DAT_060cf0fc;
extern float DAT_060cf0ec;
extern float DAT_060cf0f0;
extern float DAT_060cf0f4;

// STUB: SADX 0x0081fba0
void FUN_0081fba0(void)
{
	DAT_060cf104.textures = (struct NJS_TEXNAME *)&texlist_clight;
	DAT_060cf0f8 = 0.4f;
	*(struct NJS_TEXANIM **)&DAT_060cf104.nbTexture = (struct NJS_TEXANIM *)&anim_clight;
	DAT_060cf0fc = 0.4f;
	DAT_060cf0ec = 0.0f;
	DAT_060cf0f0 = 0.0f;
	DAT_060cf0f4 = 0.0f;
}
