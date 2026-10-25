#include "decls.h"
extern float DAT_060dbc00;
extern float DAT_060dbc04;
extern struct NJS_TEXLIST *DAT_060dbc0c;
extern float DAT_060dbbf4;
extern struct NJS_TEXANIM *DAT_060dbc10;
extern float DAT_060dbbf8;
extern float DAT_060dbbfc;

// FUNCTION: SADX 0x00869900
void CreateJetBomb(struct NJS_POINT3 *pos)
{
	struct task *var1 = CreateElementalTask(2, 6, EffectJetBomb);
	var1->twp->pos = *pos;
	DAT_060dbc00 = 5.0f;
	DAT_060dbc04 = 5.0f;
	DAT_060dbc0c = &texlist_jetbomb;
	DAT_060dbbf4 = 0.0f;
	DAT_060dbc10 = (struct NJS_TEXANIM *)&anim_bomb;
	DAT_060dbbf8 = 0.0f;
	DAT_060dbbfc = 0.0f;
	var1->disp = EffectJetBomb;
}
