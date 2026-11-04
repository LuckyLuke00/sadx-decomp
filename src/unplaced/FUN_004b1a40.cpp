#include "decls.h"
#include <string.h>
#include <new>
#include <vector>
#include "../advertise.h"
extern char DAT_05b42418[0x104];
void FUN_004b1cb0(int param_1, int param_2, int param_3, int param_4);
struct FUN_004b6590_0
{
	struct NJS_ARGB local_0;
	Magic::RenderCore::Texture *local_10;
};
struct FUN_004b2330_0
{
	FUN_004b2330_0();
	char local_0[0x104];
	int local_104;
	void *local_108;
	int local_10c;
	Magic::RenderCore::Texture *local_110;
	Magic::RenderCore::Texture *local_114;
	Magic::RenderCore::Texture *local_118;
	std::vector<FUN_004b6590_0 *> local_11c;
};
template class std::vector<FUN_004b6590_0 *>;
template class std::vector<FUN_004b2330_0 *>;
void FUN_004b5e70(int param_1);
void *FUN_0040efd0();
void FUN_004b38e0(struct FUN_004b2330_0 *param_1);

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
extern char **DAT_05b422d8;
extern char DAT_025adde0[0x20e][0x12c];
extern char *DAT_0629948c;
extern char *DAT_06299490;

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

// STUB: SADX 0x004b2330
FUN_004b2330_0::FUN_004b2330_0()
{
}

// The original allocates 0x12c bytes; the final record member remains unidentified.
// FUNCTION: SADX 0x004b23e0
void FUN_004b23e0(void *param_1, void *param_2, int param_3, const char *param_4, int param_5)
{
	int *local_c = (int *)param_1;
	std::string local_30(param_4);
	int local_8c;
	char *local_128;
	FUN_004b2330_0 *local_dc;
	unsigned int local_a0;
	FUN_004b6590_0 *local_9c;

	for (local_8c = 0; local_8c < 0x20e; local_8c++)
	{
		local_128 = DAT_025adde0[local_8c];
		if (strcmp(local_128 + 4, param_4) == 0 && *(int *)(local_128 + 0x108) == param_5 && !FUN_004b1a80((char *)param_4, param_5))
		{
			local_dc = new FUN_004b2330_0;
			strcpy_s(local_dc->local_0, 0x100, local_128 + 4);
			local_dc->local_104 = param_5;
			local_dc->local_108 = param_1;
			local_dc->local_10c = *local_c;
			local_dc->local_114 = new Magic::RenderCore::Texture;
			local_dc->local_114->Load(param_2, 1, param_3, 2, 1, 0);
			local_dc->local_118 = new Magic::RenderCore::Texture;
			local_dc->local_118->Load(param_2, 1, param_3, 2, 1, 0);
			for (local_a0 = 0; FUN_0040efd0(), local_a0 < (unsigned int)((DAT_06299490 - DAT_0629948c) / 0x94); local_a0++)
			{
				local_9c = new FUN_004b6590_0;
				FUN_0040efd0();
				local_9c->local_0 = *(NJS_ARGB *)(DAT_0629948c + local_a0 * 0x94);
				local_9c->local_10 = new Magic::RenderCore::Texture;
				local_9c->local_10->Load(param_2, 1, param_3, 2, 1, 0);
				local_dc->local_11c.push_back(local_9c);
			}
			FUN_004b38e0(local_dc);
			((std::vector<FUN_004b2330_0 *> *)&DAT_05b422dc)->push_back(local_dc);
			DAT_025addd8 = 1;
		}
	}
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

// The original includes an empty wait loop that this implementation omits.
// FUNCTION: SADX 0x004b5e70
void FUN_004b5e70(int param_1)
{
	bool local_5i;
	unsigned int local_cj;
	char *local_10m;
	char *local_14;
	unsigned int local_18i;
	char *local_1c;

	if (param_1 != 0)
	{
		local_5i = false;
		*(std::vector<FUN_004b2330_0 *>::iterator *)&DAT_05b422d8 = ((std::vector<FUN_004b2330_0 *> *)&DAT_05b422dc)->begin();
		for (local_cj = 0; local_cj < (unsigned int)(DAT_05b422e0 - DAT_05b422dc); local_cj++, (*(std::vector<FUN_004b2330_0 *>::iterator *)&DAT_05b422d8)++)
		{
			local_10m = DAT_05b422dc[local_cj];
			if (local_10m != 0 && *(int *)(local_10m + 0x108) == param_1)
			{
				local_5i = true;
				break;
			}
		}
		if (local_5i)
		{
			local_14 = *DAT_05b422d8;
			**(int **)(local_14 + 0x108) = *(int *)(local_14 + 0x10c);
			if (*(Magic::RenderCore::Texture **)(local_14 + 0x114) != 0)
			{
				(*(Magic::RenderCore::Texture **)(local_14 + 0x114))->FUN_00922750();
				delete *(Magic::RenderCore::Texture **)(local_14 + 0x114);
				*(Magic::RenderCore::Texture **)(local_14 + 0x114) = 0;
			}
			if (*(Magic::RenderCore::Texture **)(local_14 + 0x118) != 0)
			{
				(*(Magic::RenderCore::Texture **)(local_14 + 0x118))->FUN_00922750();
				delete *(Magic::RenderCore::Texture **)(local_14 + 0x118);
				*(Magic::RenderCore::Texture **)(local_14 + 0x118) = 0;
			}
			if (*(Magic::RenderCore::Texture **)(local_14 + 0x110) != 0)
			{
				(*(Magic::RenderCore::Texture **)(local_14 + 0x110))->FUN_00922750();
				delete *(Magic::RenderCore::Texture **)(local_14 + 0x110);
				*(Magic::RenderCore::Texture **)(local_14 + 0x110) = 0;
			}
			for (local_18i = 0; local_18i < ((std::vector<FUN_004b6590_0 *> *)(local_14 + 0x11c))->size(); local_18i++)
			{
				local_1c = (char *)(*(std::vector<FUN_004b6590_0 *> *)(local_14 + 0x11c))[local_18i];
				if (*(Magic::RenderCore::Texture **)(local_1c + 0x10) != 0)
				{
					(*(Magic::RenderCore::Texture **)(local_1c + 0x10))->FUN_00922750();
					delete *(Magic::RenderCore::Texture **)(local_1c + 0x10);
					*(Magic::RenderCore::Texture **)(local_1c + 0x10) = 0;
				}
			}
			((std::vector<FUN_004b2330_0 *> *)&DAT_05b422dc)->erase(*(std::vector<FUN_004b2330_0 *>::iterator *)&DAT_05b422d8);
		}
	}
}

// FUNCTION: SADX 0x004b6460
void FUN_004b6460(struct NJS_TEXLIST *param_1, char *param_2)
{
	struct NJS_TEXLIST *local_8 = param_1;
	if (local_8 != 0 && param_2 != 0)
	{
		for (unsigned int local_c = 0; local_c < local_8->nbTexture; local_c++)
		{
			struct NJS_TEXNAME *local_10 = *(struct NJS_TEXNAME **)((char *)local_8->textures + local_c * 0xc + 8);
			if (local_10 != 0)
			{
				int local_14 = *(int *)((char *)local_10 + 0x34);
				if (local_14 != 0)
				{
					memset(DAT_05b42418, 0, 0x104);
					sprintf_s(DAT_05b42418, 0x104, "%s_%d_", param_2, local_c);
					FUN_004b1cb0((int)((char *)local_10 + 0x34), local_14, (int)DAT_05b42418, 1);
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

