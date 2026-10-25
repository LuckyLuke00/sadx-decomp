#include "decls.h"
extern struct _OBJ_CAMERAPARAM *DAT_05edd128;
extern unsigned char DAT_05edd131;
extern unsigned char DAT_05edd133;
extern unsigned char DAT_05edd13c;

// FUNCTION: SADX 0x00903000
void EvChaos6Human2Water()
{
	struct _OBJ_CAMERAPARAM *var1 = DAT_05edd128;
	if (*(unsigned char *)var1 != 8)
	{
		DAT_05edd13c = 8;
		DAT_05edd131 = *(unsigned char *)var1;
	}
	DAT_05edd133 = 0x12;
}

// FUNCTION: SADX 0x00903020
void EvChaos6Water2Human()
{
	char *var1 = (char *)DAT_05edd128;
	if (*var1 != 9)
	{
		DAT_05edd13c = 9;
		DAT_05edd131 = *var1;
	}
	DAT_05edd133 = 0x11;
}
