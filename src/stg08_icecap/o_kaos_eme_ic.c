#include "decls.h"

// GLOBAL: SADX 0x045da0c8
static struct NJS_TEXANIM anim_kaos_eme[3];

// GLOBAL: SADX 0x045da0c0
static struct NJS_TEXLIST texlist_kaos_eme_eff;

extern float DAT_060dbb90;
extern float DAT_060dbb94;
extern float DAT_060dbb98;
extern float DAT_060dbb9c;
extern float DAT_060dbba0;
extern struct NJS_TEXLIST *DAT_060dbba8;
extern struct NJS_TEXANIM *DAT_060dbbac;

// FUNCTION: SADX 0x0085e210
void FUN_0085e210(void)
{
	DAT_060dbb9c = 0.35f;
	DAT_060dbba8 = &texlist_kaos_eme_eff;
	DAT_060dbba0 = 0.35f;
	DAT_060dbbac = anim_kaos_eme;
	DAT_060dbb90 = 0.0f;
	DAT_060dbb94 = 0.0f;
	DAT_060dbb98 = 0.0f;
}
