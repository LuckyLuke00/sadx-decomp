#include "decls.h"
extern long LandAttrSS[40][40];
extern long LandAttrEC[40][40];
extern long LandAttrMR[40][40];
extern char DAT_05b08850[131136];
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);

// FUNCTION: SADX 0x00442720
void AL_InitLandMark()
{
	int var1;
	int var2;

	memset(DAT_05b08850, 0, 0x20040);
	for (var1 = 0; var1 < 0x28; var1++)
	{
		for (var2 = 0; var2 < 0x28; var2++)
		{
			int var3;

			switch (AL_GetStageNumber())
			{
				case 4:
					var3 = LandAttrSS[var1][var2];
					break;
				case 5:
					var3 = LandAttrEC[var1][var2];
					break;
				case 6:
					var3 = LandAttrMR[var1][var2];
					break;
				default:
					continue;
			}
			if ((unsigned)(var3 - 1) > 0xe)
			{
				continue;
			}
			{
				int *var4 = (int *)(DAT_05b08850 + var3 * 0x2004);

				*(int *)((char *)var4 + *var4 * 8 + 8) = var1;
				*(int *)((char *)var4 + *var4 * 8 + 4) = var2;
				*var4 = *var4 + 1;
			}
		}
	}
}
