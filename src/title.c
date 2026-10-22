#include "decls.h"
extern void njPrintColor(unsigned long);
extern void njPrintC(int, char const *);
extern int DAT_05cda0c8;
extern int DAT_05cda0e4;

// FUNCTION: SADX 0x0059abe0
void EndDisplayPress(struct task *tp)
{
	late_ReleaseTexture(&texlist_pressstart);
}

// STUB: SADX 0x0059acb0
void TitleSetStageNumber()
{
}

// STUB: SADX 0x0059b280
void DisplayTitle_ss()
{
}

// STUB: SADX 0x0059b370
void DisplaySelectingCharacter_ss()
{
}

// STUB: SADX 0x0059b550
void DisplaySelectingSequence()
{
}

// FUNCTION: SADX 0x0059b630
void FUN_0059b630(void)
{
	if ((DAT_05cda0c8 & 0x10) == 0)
	{
		njPrintColor(0xffff0000);
		njPrintC(0x20010, "<<");
		njPrintColor(-1);
	}
}

// FUNCTION: SADX 0x0059b670
void FUN_0059b670(void)
{
	if ((DAT_05cda0c8 & 0x10) == 0)
	{
		njPrintColor(0xffff0000);
		njPrintC(0x220010, ">>");
		njPrintColor(0xffffffff);
	}
}

// FUNCTION: SADX 0x0059b6b0
void dsSetFade(int fade_lev)
{
	DAT_05cda0e4 = fade_lev;
}

// STUB: SADX 0x0059b6c0
int FUN_0059b6c0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0059b720
void dsDispFadeBlack()
{
}

// STUB: SADX 0x0059b7c0
void dsDispFadeWhite()
{
}
