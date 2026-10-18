#include "decls.h"
#include <string.h>

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
	int result = 0;

	while (param_1 != 0 && *param_1 != 0x24)
	{
		if (*param_1 == param_2)
		{
			result = 1;
		}
		param_1++;
	}
	return result;
}

// FUNCTION: SADX 0x004b1a80
bool FUN_004b1a80(char *param_1, int param_2)
{
	for (unsigned int i = 0; i < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); i++)
	{
		char **it = DAT_05b422dc + i;
		if (!strcmp(*it, param_1) && *(int *)(DAT_05b422dc[i] + 0x104) == param_2)
		{
			return true;
		}
	}
	return false;
}

// FUNCTION: SADX 0x004b2860
unsigned char FUN_004b2860(unsigned char param_1, unsigned char param_2, unsigned char param_3)
{
	float f = param_3 / 255.0;
	unsigned short b = param_2;
	unsigned short a = param_1;
	return (unsigned char)(b * f + (1.0f - f) * a);
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
	unsigned int hyk;
	unsigned int rl;
	char *mog;
	unsigned int i;
	unsigned int cm;
	char *dz;
	unsigned int qu;
	char *ddcu;
	unsigned int crbm;
	char *faqf;
	char ***des;
	char **jtb;
	char *t;
	char ***o;

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
			hyk = 0;
			for (rl = 0; rl < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); rl++)
			{
				mog = DAT_05b422dc[rl];
				for (i = 0; des = (char ***)(mog + 0x11c), i < (unsigned int)(des[1] - des[0]); i++)
				{
					jtb = *(char ***)(mog + 0x11c) + i;
					t = *jtb;
					if ((int)!memcmp(t, &DAT_05ad9654, 0x10))
					{
						hyk = i;
					}
				}
			}
			for (cm = 0; cm < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); cm++)
			{
				dz = DAT_05b422dc[cm];
				if (dz)
				{
					o = (char ***)(dz + 0x11c);
					if ((unsigned int)(o[1] - o[0]) > 0 && dz && *(int *)((*(char ***)(dz + 0x11c))[hyk] + 0x10) && *(int *)(dz + 0x108))
					{
						**(int **)(dz + 0x108) = *(int *)((*(char ***)(dz + 0x11c))[hyk] + 0x10);
						DAT_05b423fc = 1;
					}
				}
			}
		}
		else
		{
			if ((int)!memcmp(&DAT_05ad9654, &DAT_025adbf8, 0x10))
			{
				for (qu = 0; qu < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); qu++)
				{
					ddcu = DAT_05b422dc[qu];
					if (ddcu && *(int *)(ddcu + 0x118) && *(int *)(ddcu + 0x108))
					{
						**(int **)(ddcu + 0x108) = *(int *)(ddcu + 0x118);
						DAT_05b423fc = 1;
					}
				}
			}
			else
			{
				for (crbm = 0; crbm < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); crbm++)
				{
					faqf = DAT_05b422dc[crbm];
					if (faqf && *(int *)(faqf + 0x114) && *(int *)(faqf + 0x108))
					{
						**(int **)(faqf + 0x108) = *(int *)(faqf + 0x114);
						DAT_05b423fc = 1;
					}
				}
			}
		}
	}
}

// FUNCTION: SADX 0x004b6a60
void FUN_004b6a60(int param_1, int *param_2, int *param_3)
{
	void *a = param_2;
	int *b;
	int *d;
	void *c = a;
	if (c)
	{
		*(int *)c = *param_3;
		d = (int *)c;
	}
	else
	{
		d = 0;
	}
	b = d;
}
