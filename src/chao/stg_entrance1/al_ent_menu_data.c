#include "decls.h"
extern struct NJS_SPRITE DAT_060eea04;
extern void SetMatMatMaterial();
extern void CalcScreenRaito_SPR2D_CR(struct NJS_SPRITE *spr);
extern void late_DrawSprite2D(struct NJS_SPRITE *sp, int n, float pri, unsigned long atr, int flgs);
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

// FUNCTION: SADX 0x00472a10
void AL_EntranceDrawSprite2D(struct NJS_SPRITE *pSprite, long SpriteNum, float zpos)
{
	float local_10;
	float local_c;
	int local_8;

	SetMatMatMaterial();
	CalcScreenRaito_SPR2D_CR(pSprite);
	local_10 = zpos;
	local_c = -3.0f;
	local_8 = *(short *)((char *)pSprite->tanim + 0x12 + (long)SpriteNum * 0x14);
	if (local_10 >= local_c && local_10 < 12048.0f)
	{
		local_10 = local_10 + 22048.0f;
	}
	late_DrawSprite2D(&DAT_060eea04, (int)SpriteNum, local_10, (unsigned long)local_8, 4);
}
