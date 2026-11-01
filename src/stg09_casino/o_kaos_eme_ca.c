#include "decls.h"

// GLOBAL: SADX 0x0480d898
static struct NJS_TEXANIM anim_kaos_eme[3];

// GLOBAL: SADX 0x0480d890
static struct NJS_TEXLIST texlist_kaos_eme_eff;

extern float DAT_060dc4a4;
extern float DAT_060dc4a8;
extern float DAT_060dc4ac;
extern float DAT_060dc4b0;
extern float DAT_060dc4b4;
extern struct NJS_TEXLIST *DAT_060dc4bc;
extern struct NJS_TEXANIM *DAT_060dc4c0;

// FUNCTION: SADX 0x008881a0
void FUN_008881a0(void)
{
	DAT_060dc4b0 = 0.35f;
	DAT_060dc4bc = &texlist_kaos_eme_eff;
	DAT_060dc4b4 = 0.35f;
	DAT_060dc4c0 = anim_kaos_eme;
	DAT_060dc4a4 = 0.0f;
	DAT_060dc4a8 = 0.0f;
	DAT_060dc4ac = 0.0f;
}
