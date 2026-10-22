#include "decls.h"

// FUNCTION: SADX 0x006047e0
void FUN_006047e0(int param_1)
{
	*(int *)(param_1 + 0x18) = 0;
	*(int *)(param_1 + 0x38) = 0;
}

// FUNCTION: SADX 0x006049a0
void FUN_006049a0(int param_1)
{
	AvaLoadTexForEachMode((AdvaModeEnum)4);
	ghLoadFontTexture((struct GH_FONT_INFO *)&Ascii16x16FontInfo);
	ghSelectFont((struct GH_FONT_INFO *)&Ascii16x16FontInfo);
	SetAdvaBGM(-1);
	SetAdvaSerifu((AvaSerifuModeEnum)6);
	*(char *)(param_1 + 0x35) = 0;
	*(char *)(param_1 + 0x36) = 0;
	FUN_006047e0(param_1);
}

// STUB: SADX 0x00605830
void FUN_00605830(unsigned long c0, unsigned long c1, float avg)
{
}
