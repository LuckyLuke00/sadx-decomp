#include "decls.h"
extern struct NJS_TEXLIST texlist_obj_finalegg;
extern struct NJS_TEXLIST texlist_unyo;
void FUN_007d21b0(void *param_1);

// FUNCTION: SADX 0x0088e530
void TexMakeInit()
{
	texlist_unyo.textures = (NJS_TEXNAME *)((char *)texlist_obj_finalegg.textures + 0x7f8);
	texlist_unyo.nbTexture = 6;
}

// STUB: SADX 0x0088e670
void ObjectFinalEggTexAnime(struct task *tp)
{
}
