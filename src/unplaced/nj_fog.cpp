#include "decls.h"
extern int DAT_05ada5b4;

// FUNCTION: SADX 0x00435b20
void njFogEnable(void)
{
	stFogEnable();
	DAT_05ada5b4 = 1;
}

// FUNCTION: SADX 0x00435b30
void njFogDisable(void)
{
	stFogDisable();
	DAT_05ada5b4 = 0;
}

// FUNCTION: SADX 0x00435b40
void njSetFogColor(unsigned long c)
{
	stFogColor(c);
}

// FUNCTION: SADX 0x00435b50
void njSetFogTable(float * const fog)
{
	stSetFogTable(fog);
}
