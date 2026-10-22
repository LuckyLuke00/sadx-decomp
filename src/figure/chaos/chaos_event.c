#include "decls.h"
extern unsigned char DAT_05edd13f;
extern unsigned char DAT_05edd140;

// FUNCTION: SADX 0x008c5b80
void EvChaosInit()
{
	DAT_05edd13f = 1;
	DAT_05edd140 = 0;
}

// FUNCTION: SADX 0x008c5ba0
void EvChaosExit()
{
	DAT_05edd140 = 1;
}
