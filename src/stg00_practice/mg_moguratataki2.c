#include "decls.h"
extern int DAT_060ce908;
extern int *DAT_060ce904;
extern int DAT_05ccdaa0;
extern int DAT_05ccdaa4;
extern int DAT_05ccdaa8;
extern int DAT_05ccdaac;
extern int DAT_05ccdab0;
extern int DAT_05ccdab4;

// FUNCTION: SADX 0x007f30c0
void FUN_007f30c0(unsigned char *param_1)
{
	int var1 = *DAT_060ce904;
	*DAT_060ce904 = var1 - 1;
	if (var1 <= 0)
	{
		*param_1 = 3;
		dsPlay_oneshot(0x23f, 0, 0, 0);
		DAT_05ccdaa0 = 0;
		DAT_05ccdaa4 = 0x1f4;
		DAT_05ccdaa8 = 0;
		DAT_05ccdaac = 0x64;
		DAT_05ccdab0 = 0;
		DAT_05ccdab4 = -0xc8;
	}
}

// STUB: SADX 0x007f4410
void FUN_007f4410(void)
{
}

// STUB: SADX 0x007f4490
void DisplayLoading()
{
}

// FUNCTION: SADX 0x007f4560
void EndMoguraScore()
{
	DAT_060ce908 = 1;
}
