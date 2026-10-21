#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_ARGB DAT_05b3e040;
extern unsigned char DAT_025acd84;
extern unsigned char DAT_05b3e065;
void FUN_00573100();

// FUNCTION: SADX 0x005730b0
void ___njFogEnable()
{
	if (DAT_05b9d838 != 0)
		return;
	if (*((unsigned char *)&DAT_05b3e040 + 12) != 0)
	{
		if (setfog() != 0)
		{
			if ((DAT_025acd84 & 1) == 0)
				njFogEnable();
			else
				njFogDisable();
		}
		DAT_05b3e065 = 1;
	}
	else
	{
		FUN_00573100();
		njFogDisable();
	}
}

// FUNCTION: SADX 0x00573260
void ___njFogDisable(void)
{
	if (DAT_05b9d838 != 0)
		return;
	DAT_05b3e065 = 0;
	njFogDisable();
}
