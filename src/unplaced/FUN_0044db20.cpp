#include "decls.h"
extern int DAT_05b31398;
void AlMsgFontExit();

// FUNCTION: SADX 0x0044db20
void FUN_0044db20()
{
	if (--DAT_05b31398 == 0)
		AlMsgFontExit();
}
