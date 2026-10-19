#include "decls.h"
extern unsigned char DAT_05cda118;
extern struct GH_FONT_INFO StaffRollFontInfo[];

// FUNCTION: SADX 0x0059bc90
void AvaExitDispLoading()
{
	if (DAT_05cda118 == 1)
	{
		ghReleaseFontTexture(StaffRollFontInfo);
	}
	DAT_05cda118 = 0;
}
