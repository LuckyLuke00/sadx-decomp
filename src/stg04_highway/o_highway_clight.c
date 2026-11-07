#include "decls.h"

// GLOBAL: SADX 0x03e71b40
static struct NJS_TEXANIM anim_clight[1];

extern struct NJS_SPRITE DAT_060cf0ec;

// FUNCTION: SADX 0x0081fba0
void FUN_0081fba0(void)
{
	DAT_060cf0ec.tlist = &texlist_clight;
	DAT_060cf0ec.sx = 0.4f;
	DAT_060cf0ec.tanim = anim_clight;
	DAT_060cf0ec.sy = 0.4f;
	DAT_060cf0ec.p.x = 0.0f;
	DAT_060cf0ec.p.y = 0.0f;
	DAT_060cf0ec.p.z = 0.0f;
}
