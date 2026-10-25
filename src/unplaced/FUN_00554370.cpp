#include "decls.h"
extern char DAT_05bafd0c[8];
extern unsigned char DAT_05bafb00[];
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

// STUB: SADX 0x00554390
unsigned short FUN_00554390(char *param_1)
{
	return (unsigned short)0;
}

// FUNCTION: SADX 0x00554430
void FUN_00554430(int param_1)
{
	int local_8g;
	int local_10;
	int local_cj;
	for (local_8g = 0; local_8g < 0x200; local_8g = local_8g + 1)
	{
		if (local_8g % 8 == 0)
		{
			*((char *)param_1 + local_8g / 8 + 0x260) = 0;
		}
		if (DAT_05bafb00[local_8g] == 1)
		{
			local_10 = local_8g / 8;
			local_cj = 1 << (local_8g % 8);
			*((char *)param_1 + local_10 + 0x260) |= local_cj;
		}
	}
}

// FUNCTION: SADX 0x005544e0
void FUN_005544e0(char *param_1)
{
	int local_8g;
	int local_10;
	int local_cj;
	for (local_8g = 0; local_8g < 0x200; local_8g = local_8g + 1)
	{
		if (local_8g % 8 == 0)
		{
			*(char *)(param_1 + local_8g / 8 + 0x2a0) = 0;
		}
		if (DAT_05baf900[local_8g] == 1)
		{
			local_10 = local_8g / 8;
			local_cj = 1 << (local_8g % 8);
			*(char *)(param_1 + local_10 + 0x2a0) |= local_cj;
		}
	}
}

// FUNCTION: SADX 0x00554590
void FUN_00554590(char *param_1)
{
	int local_8;
	for (local_8 = 0; local_8 < 8; local_8++)
	{
		*(char *)(param_1 + local_8 + 0x2e0) = DAT_05bafd0c[local_8];
	}
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

// FUNCTION: SADX 0x00554770
void FUN_00554770(int param_1)
{
	int local_8g;
	int local_cg;
	for (local_8g = 0; local_8g < 0x200; local_8g = local_8g + 1)
	{
		if (local_8g % 8 == 0)
		{
			local_cg = *(char *)((char *)param_1 + local_8g / 8 + 0x260);
		}
		if (local_cg & 1)
		{
			DAT_05bafb00[local_8g] = 1;
		}
		else
		{
			DAT_05bafb00[local_8g] = 0;
		}
		local_cg = local_cg >> 1;
	}
}

// FUNCTION: SADX 0x005547f0
void FUN_005547f0(char *param_1)
{
	int local_8g;
	int local_cg;
	for (local_8g = 0; local_8g < 0x200; local_8g = local_8g + 1)
	{
		if (local_8g % 8 == 0)
		{
			local_cg = (char)*(param_1 + local_8g / 8 + 0x2a0);
		}
		if (local_cg & 1)
		{
			DAT_05baf900[local_8g] = 1;
		}
		else
		{
			DAT_05baf900[local_8g] = 0;
		}
		local_cg = local_cg >> 1;
	}
}

// FUNCTION: SADX 0x00554870
void FUN_00554870(char *param_1)
{
	int local_8;
	for (local_8 = 0; local_8 < 8; local_8++)
	{
		DAT_05bafd0c[local_8] = param_1[local_8 + 0x2e0];
	}
}

// STUB: SADX 0x005548b0
void FUN_005548b0(char *param_1)
{
}
