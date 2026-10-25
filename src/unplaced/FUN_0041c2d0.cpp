#include "decls.h"
extern void *DAT_05ab42dc;
extern void *DAT_05ab42e0;

// FUNCTION: SADX 0x0041c2d0
void FUN_0041c2d0(void *param_1)
{
	int var1;
	var1 = (int)DAT_05ab42dc;
	if (DAT_05ab42dc != DAT_05ab42e0)
	{
		do
		{
			if (*(int *)(var1 + 0x14) == (int)param_1)
			{
				*(int *)(var1 + 0x14) = 0;
			}
			var1 += 0x2c;
		} while (var1 != (int)DAT_05ab42e0);
	}
}
