#include "decls.h"
extern int DAT_026d7ec8;

// FUNCTION: SADX 0x0067d410
void chInitRandom(unsigned long param_1)
{
	DAT_026d7ec8 = param_1;
}

// STUB: SADX 0x0067d420
unsigned long chRandomU32(void)
{
	return (unsigned long)0;
}
