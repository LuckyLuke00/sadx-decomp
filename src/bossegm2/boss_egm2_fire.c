#include "decls.h"
extern struct NJS_SPRITE DAT_060b9f8c;
extern struct NJS_TEXLIST texlist_egm2_fire;
extern struct NJS_TEXANIM anim_kaen[];

// FUNCTION: SADX 0x006ca460
void Egm2_Fire_Init()
{
	initSpriteSub(&DAT_060b9f8c, &texlist_egm2_fire, &anim_kaen[0]);
}
