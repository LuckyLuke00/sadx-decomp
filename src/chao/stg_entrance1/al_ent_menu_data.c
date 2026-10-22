#include "decls.h"
extern int DAT_05b3ebbc;
extern const struct SAlEntAnimArray *DAT_05b3301c;
extern const struct SAlEntAnimArray *DAT_05b33020;
extern const struct SAlEntAnimArray gAlEntAnimArray_char_e[];
extern const struct SAlEntAnimArray gAlEntAnimArray_char_j[];
extern const struct SAlEntAnimArray gAlEntAnimArray_title_e[];
extern const struct SAlEntAnimArray gAlEntAnimArray_title_j[];

// FUNCTION: SADX 0x004729d0
void AlEntAnimArrayInit()
{
	if (DAT_05b3ebbc != 0)
	{
		DAT_05b33020 = &gAlEntAnimArray_title_e[0];
		DAT_05b3301c = &gAlEntAnimArray_char_e[0];
	}
	else
	{
		DAT_05b33020 = &gAlEntAnimArray_title_j[0];
		DAT_05b3301c = &gAlEntAnimArray_char_j[0];
	}
}

// STUB: SADX 0x00472a10
void AL_EntranceDrawSprite2D(struct NJS_SPRITE *pSprite, long SpriteNum, float zpos)
{
}
