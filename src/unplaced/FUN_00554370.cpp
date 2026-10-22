#include "decls.h"
extern char DAT_05baf6b8;
extern short DAT_05baf6ba;
extern short DAT_05baf6bc;
extern short DAT_05baf6be;
extern unsigned short DAT_05baf6c0;
extern char DAT_05baf548[0x2b * 4];

// STUB: SADX 0x00554370
void FUN_00554370(unsigned short *param_1)
{
}

// STUB: SADX 0x00554590
void FUN_00554590(char *param_1)
{
}

// FUNCTION: SADX 0x005545d0
void FUN_005545d0(char *param_1)
{
	int local_8g;
	int local_cg;
	for (local_8g = 0; local_8g < 8; local_8g = local_8g + 1)
	{
		for (local_cg = 0; local_cg < 0x2b; local_cg = local_cg + 1)
		{
			param_1[local_8g * 0x2b + local_cg + 0x348] = DAT_05baf548[local_8g * 0x2b + local_cg];
		}
	}
}

// FUNCTION: SADX 0x00554640
void FUN_00554640()
{
	if ((DAT_05baf6b8 == 2) && (DAT_05baf6ba == 2) && (DAT_05baf6bc == 7) && (DAT_05baf6be == 0) && (DAT_05baf6c0 == 0x2200))
	{
		DAT_05baf6c0 = 0x2100;
	}
}

// STUB: SADX 0x00554770
void FUN_00554770(int param_1)
{
}

// STUB: SADX 0x005547f0
void FUN_005547f0(char *param_1)
{
}

// STUB: SADX 0x00554870
void FUN_00554870(char *param_1)
{
}

// STUB: SADX 0x005548b0
void FUN_005548b0(char *param_1)
{
}
