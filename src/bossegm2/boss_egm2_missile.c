#include "decls.h"
extern struct NJS_SPRITE DAT_060b9fac;
extern struct NJS_TEXLIST texlist_egm2_missile;
extern struct NJS_TEXANIM anim_missile[];

// FUNCTION: SADX 0x006caec0
void Egm2_Missile_Init()
{
	initSpriteSub(&DAT_060b9fac, &texlist_egm2_missile, &anim_missile[0]);
}
