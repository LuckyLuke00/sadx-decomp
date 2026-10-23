#include "decls.h"
extern struct NJS_TEXLIST texlist_kaos_eme_eff;
extern struct NJS_TEXANIM anim_kaos_eme[1];
extern float DAT_060cee78;
extern float DAT_060cee7c;
extern float DAT_060cee80;
extern float DAT_060cee84;
extern float DAT_060cee88;
extern struct NJS_TEXLIST *DAT_060cee90;
extern struct NJS_TEXANIM *DAT_060cee94;

// FUNCTION: SADX 0x00805f40
void FUN_00805f40(void)
{
	DAT_060cee84 = 0.35f;
	DAT_060cee90 = &texlist_kaos_eme_eff;
	DAT_060cee88 = 0.35f;
	DAT_060cee94 = anim_kaos_eme;
	DAT_060cee78 = 0.0f;
	DAT_060cee7c = 0.0f;
	DAT_060cee80 = 0.0f;
}

// STUB: SADX 0x00805f80
void CheckGameClear(struct task *tp)
{
}
