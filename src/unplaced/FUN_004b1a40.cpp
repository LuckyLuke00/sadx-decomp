#include "decls.h"
#include <string.h>
#include <new>
void *FUN_004b6ae0(unsigned int param_1);
void FUN_004b66c0(void **param_1);
void FUN_004b6720(void *param_1, void *param_2, void *param_3);
void FUN_004b5e70(int param_1);

extern char **DAT_05b422dc;
extern char **DAT_05b422e0;
extern unsigned int DAT_05b42414;
extern int DAT_05b42400;
extern struct NJS_ARGB DAT_05b42404;
extern struct NJS_ARGB DAT_025adbd8;
extern struct NJS_ARGB DAT_05ad9654;
extern struct NJS_ARGB DAT_05b40a4c;
extern struct NJS_ARGB DAT_025adbf8;
extern unsigned char DAT_025addd8;
extern unsigned char DAT_05b423fc;

// FUNCTION: SADX 0x004b1a40
int FUN_004b1a40(int *param_1, int param_2)
{
	int local_8 = 0;

	while (param_1 != 0 && *param_1 != 0x24)
	{
		if (*param_1 == param_2)
		{
			local_8 = 1;
		}
		param_1++;
	}
	return local_8;
}

// FUNCTION: SADX 0x004b1a80
bool FUN_004b1a80(char *param_1, int param_2)
{
	for (unsigned int local_8 = 0; local_8 < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); local_8++)
	{
		char **local_c = DAT_05b422dc + local_8;
		if (!strcmp(*local_c, param_1) && *(int *)(DAT_05b422dc[local_8] + 0x104) == param_2)
		{
			return true;
		}
	}
	return false;
}

// FUNCTION: SADX 0x004b2860
unsigned char FUN_004b2860(unsigned char param_1, unsigned char param_2, unsigned char param_3)
{
	float local_ci = param_3 / 255.0;
	unsigned short local_10 = param_2;
	unsigned short local_8g = param_1;
	return (unsigned char)(local_10 * local_ci + (1.0f - local_ci) * local_8g);
}

// FUNCTION: SADX 0x004b3210
bool FUN_004b3210(int *param_1, int *param_2)
{
	if (param_1[0] < param_2[2] && param_1[2] > param_2[0] && param_1[1] < param_2[3] && param_1[3] > param_2[1])
	{
		return true;
	}
	return false;
}

// FUNCTION: SADX 0x004b5ad0
void FUN_004b5ad0(void)
{
	unsigned int local_8gk;
	unsigned int local_ci;
	char *local_10hk;
	unsigned int local_14k;
	unsigned int local_18go;
	char *local_1co;
	unsigned int local_20go;
	char *local_24gl;
	unsigned int local_28g;
	char *local_2cgm;
	char ***local_30k;
	char **local_34q;
	char *local_38g;
	char ***local_3cj;

	if (!(DAT_05b42414 & 1))
	{
		DAT_05b42414 |= 1;
		DAT_05b42404 = DAT_025adbd8;
	}
	if (((int)!(int)!memcmp(&DAT_05b42404, &DAT_05ad9654, 0x10) || DAT_05b42400 != DAT_05b422e0 - DAT_05b422dc) && DAT_025addd8)
	{
		if (DAT_05b423fc)
		{
			DAT_05b42404 = DAT_05ad9654;
			DAT_05b42400 = DAT_05b422e0 - DAT_05b422dc;
		}
		if ((int)!(int)!memcmp(&DAT_05ad9654, &DAT_05b40a4c, 0x10) && (int)!(int)!memcmp(&DAT_05ad9654, &DAT_025adbf8, 0x10))
		{
			local_8gk = 0;
			for (local_ci = 0; local_ci < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); local_ci++)
			{
				local_10hk = DAT_05b422dc[local_ci];
				for (local_14k = 0; local_30k = (char ***)(local_10hk + 0x11c), local_14k < (unsigned int)(local_30k[1] - local_30k[0]); local_14k++)
				{
					local_34q = *(char ***)(local_10hk + 0x11c) + local_14k;
					local_38g = *local_34q;
					if ((int)!memcmp(local_38g, &DAT_05ad9654, 0x10))
					{
						local_8gk = local_14k;
					}
				}
			}
			for (local_18go = 0; local_18go < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); local_18go++)
			{
				local_1co = DAT_05b422dc[local_18go];
				if (local_1co)
				{
					local_3cj = (char ***)(local_1co + 0x11c);
					if ((unsigned int)(local_3cj[1] - local_3cj[0]) > 0 && local_1co && *(int *)((*(char ***)(local_1co + 0x11c))[local_8gk] + 0x10) && *(int *)(local_1co + 0x108))
					{
						**(int **)(local_1co + 0x108) = *(int *)((*(char ***)(local_1co + 0x11c))[local_8gk] + 0x10);
						DAT_05b423fc = 1;
					}
				}
			}
		}
		else
		{
			if ((int)!memcmp(&DAT_05ad9654, &DAT_025adbf8, 0x10))
			{
				for (local_20go = 0; local_20go < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); local_20go++)
				{
					local_24gl = DAT_05b422dc[local_20go];
					if (local_24gl && *(int *)(local_24gl + 0x118) && *(int *)(local_24gl + 0x108))
					{
						**(int **)(local_24gl + 0x108) = *(int *)(local_24gl + 0x118);
						DAT_05b423fc = 1;
					}
				}
			}
			else
			{
				for (local_28g = 0; local_28g < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); local_28g++)
				{
					local_2cgm = DAT_05b422dc[local_28g];
					if (local_2cgm && *(int *)(local_2cgm + 0x114) && *(int *)(local_2cgm + 0x108))
					{
						**(int **)(local_2cgm + 0x108) = *(int *)(local_2cgm + 0x114);
						DAT_05b423fc = 1;
					}
				}
			}
		}
	}
}

// FUNCTION: SADX 0x004b6520
void FUN_004b6520(int param_1)
{
	int *local_8 = (int *)param_1;
	if (local_8 != 0)
	{
		for (unsigned int local_c = 0; local_c < (unsigned int)local_8[1]; local_c++)
		{
			int local_10 = *(int *)(*local_8 + local_c * 0xc + 8);
			if (local_10 != 0)
			{
				int local_14 = *(int *)(local_10 + 0x34);
				if (local_14 != 0)
				{
					FUN_004b5e70(local_10 + 0x34);
				}
			}
		}
	}
}

// FUNCTION: SADX 0x004b6590
void __fastcall FUN_004b6590(int *param_1)
{
	int local_18o;
	int local_20k;
	int local_14s;
	int local_10l;
	int local_ci;
	int local_8g;
	int local_24;
	int local_1cg;

	local_18o = *(int *)param_1;
	local_14s = *(int *)(param_1 + 1);
	local_24 = local_14s;
	local_1cg = local_24;
	local_20k = *(int *)param_1;
	local_ci = local_20k;
	local_8g = local_ci;
	FUN_004b6720(&local_10l, (void *)local_8g, (void *)local_1cg);
	return;
}

// FUNCTION: SADX 0x004b66c0
void FUN_004b66c0(void **param_1)
{
	void **local_8 = param_1;
	if (*local_8 != 0)
	{
		int local_10l = (int)((char *)local_8[2] - (char *)local_8[0]) >> 2;
		void *local_c = *local_8;
		char local_14[4];
		local_14[0] = 0;
		delete local_c;
	}
	*local_8 = 0;
	local_8[1] = 0;
	local_8[2] = 0;
}

// FUNCTION: SADX 0x004b6860
int FUN_004b6860(int *param_1, int param_2)
{
	unsigned int local_ci = (*(int *)(param_1 + 2) - *(int *)param_1) >> 2;
	unsigned int local_8g;
	if (0x3fffffff >= local_ci)
	{
		local_8g = 0x3fffffff;
	}
	else
	{
		local_8g = local_ci;
	}
	unsigned int local_10;
	if (local_8g - (local_ci >> 1) < local_ci)
	{
		local_10 = 0;
	}
	else
	{
		local_10 = (local_ci >> 1) + local_ci;
	}
	if (local_10 < param_2)
	{
		local_10 = param_2;
	}
	return local_10;
}

// FUNCTION: SADX 0x004b6a60
void FUN_004b6a60(int param_1, int *param_2, int *param_3)
{
	void *local_8g = param_2;
	int *local_cj;
	int *local_14;
	void *local_10 = local_8g;
	if (local_10)
	{
		*(int *)local_10 = *param_3;
		local_14 = (int *)local_10;
	}
	else
	{
		local_14 = 0;
	}
	local_cj = local_14;
}

// FUNCTION: SADX 0x004b6aa0
void FUN_004b6aa0(int param_1, int *param_2, int *param_3)
{
	int *local_8g;
	int *local_cj;
	int *local_10;
	local_cj = param_2;
	if (local_cj)
	{
		*local_cj = *param_3;
		local_10 = local_cj;
	}
	else
	{
		local_10 = 0;
	}
	local_8g = local_10;
}

// FUNCTION: SADX 0x004b6ae0
void *FUN_004b6ae0(unsigned int param_1)
{
	void *local_8 = 0;
	if (param_1 == 0)
	{
		param_1 = 0;
		return local_8;
	}
	if (param_1 > 0x3fffffff || (local_8 = operator new(param_1 * 4)) == 0)
	{
		throw std::bad_alloc();
	}
	return local_8;
}
