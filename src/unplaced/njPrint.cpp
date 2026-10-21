#include "decls.h"
extern int DAT_05ad95ec;

// FUNCTION: SADX 0x00423ea0
void njExitPrint(void)
{
	gjPrintExit();
}

// FUNCTION: SADX 0x00423ed0
void njPrintColor(unsigned long param_1)
{
	DAT_05ad95ec = param_1;
}
