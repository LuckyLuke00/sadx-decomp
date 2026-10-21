#include "decls.h"
extern int DAT_05cda0e4;

// FUNCTION: SADX 0x0059abe0
void EndDisplayPress(struct task *tp)
{
	late_ReleaseTexture(&texlist_pressstart);
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
