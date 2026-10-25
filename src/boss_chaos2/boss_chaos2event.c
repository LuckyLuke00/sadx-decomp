#include "decls.h"
extern struct PL_ACTION chaos2_action[14];
extern char DAT_05edd13e;
extern struct PL_ACTION *DAT_05edd134;
extern struct _OBJ_CAMERAPARAM *DAT_05edd128;
extern unsigned char DAT_05edd131;
extern unsigned char DAT_05edd133;
extern unsigned char DAT_05edd13c;

// FUNCTION: SADX 0x00902f90
void EvChaos2Human2Water()
{
	char *var1 = (char *)DAT_05edd128;
	if (*var1 != 8)
	{
		DAT_05edd13c = 8;
		DAT_05edd131 = *var1;
	}
	DAT_05edd133 = 0x13;
}

// FUNCTION: SADX 0x00902fb0
void EvChaos2Water2Human()
{
	struct _OBJ_CAMERAPARAM *var1 = DAT_05edd128;
	if (*(char *)var1 != 9)
	{
		DAT_05edd13c = 9;
		DAT_05edd131 = *(char *)var1;
	}
	DAT_05edd133 = 0x12;
}

// FUNCTION: SADX 0x00902fd0
void EvChaos2Action(float ratio)
{
	struct PL_ACTION *var1 = DAT_05edd134;
	DAT_05edd13e &= 0xfd;
	*(unsigned short *)((char *)var1 + 8) = 0xd;
	chaos2_action[13].racio = ratio;
}
