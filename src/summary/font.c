#include "decls.h"
extern struct GH_FONT_INFO DAT_05b9d800;
extern struct GH_FONT_INFO *DAT_05b9d828;
extern float DAT_05b9d82c;
extern float DAT_05b9d7fc;

// FUNCTION: SADX 0x004cb340
void ghLoadFontTexture(struct GH_FONT_INFO *font)
{
	if (font != 0)
	{
		DAT_05b9d828 = font;
		DAT_05b9d82c = font->char_width;
		DAT_05b9d7fc = font->char_height;
		if (font->texlist != 0)
		{
			NeonuLoadTexture(font->texlist);
		}
	}
}

// FUNCTION: SADX 0x004cb390
void ghReleaseFontTexture(struct GH_FONT_INFO *font)
{
	if (font->texlist != 0)
	{
		late_ReleaseTexture(font->texlist);
	}
}

// FUNCTION: SADX 0x004cb3b0
void ghSelectFont(struct GH_FONT_INFO *font)
{
	DAT_05b9d800 = *font;
}

// STUB: SADX 0x004cb720
int ghGetFontStrLen(char *str)
{
	return (int)0;
}

// FUNCTION: SADX 0x004cb790
struct GH_FONT_INFO GetCurFontInfo()
{
	return DAT_05b9d800;
}

// FUNCTION: SADX 0x004cb7b0
void SetCurFontInfo(struct GH_FONT_INFO info)
{
	DAT_05b9d800 = info;
}
