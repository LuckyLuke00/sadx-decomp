#include "decls.h"
struct NJS_TEXMEMLIST;
extern int DAT_05ab6820[0x180];
extern int DAT_05ab6ec0;
void _stRectangleHalf(void *param_1, void *param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5);
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);

// STUB: SADX 0x0042a1e0
void _stExpandVectorQuantizationLinear(void *param_1, void *param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
}

// STUB: SADX 0x0042a6e0
void _stTwiddledToLinear4bpp(void *param_1, void *param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
}

// FUNCTION: SADX 0x0042a7b0
void FUN_0042a7b0(void *param_1, void *param_2, int param_3, int param_4, int param_5)
{
	memcpy(param_1, param_2, param_3 * param_4 * param_5);
}

// STUB: SADX 0x0042a930
void _stRectangleHalf(void *param_1, void *param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
}

// STUB: SADX 0x0042a9a0
void _stTwiddledToLinearHalf(void *param_1, void *param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
}

// STUB: SADX 0x0042aa50
void FUN_0042aa50(void)
{
}

// STUB: SADX 0x0042ae90
void stLoadTexture(struct NJS_TEXMEMLIST *param_1, void *param_2)
{
}

// FUNCTION: SADX 0x0042b010
void stSetPaletteBank(long param_1)
{
	int var1;
	int *var2;
	var2 = &DAT_05ab6820[0];
	var1 = 0;
	do
	{
		if (*var2 == param_1)
		{
			DAT_05ab6ec0 = var2[2];
			return;
		}
		var1++;
		var2 += 3;
	} while (var1 != 0x80);
}
