#include "decls.h"
extern int DAT_05b31398;
void FPpInit();
void AlMsgFontInit();
void FUN_0044ce30();
void FUN_0044d160();

// FUNCTION: SADX 0x0044daf0
void FUN_0044daf0()
{
	int var1 = DAT_05b31398;
	DAT_05b31398 = DAT_05b31398 + 1;
	if (var1 == 0)
	{
		FPpInit();
		AlMsgFontInit();
		FUN_0044ce30();
		FUN_0044d160();
	}
}
