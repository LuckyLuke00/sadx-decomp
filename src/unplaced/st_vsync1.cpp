#include "decls.h"
extern int DAT_05ad9ad0;

// FUNCTION: SADX 0x00430d60
void stHWVSyncServerDelete(int param_1)
{
	int var1;
	var1 = (int)&DAT_05ad9ad0;
	do
	{
		if (*(int *)var1 == param_1)
		{
			*(int *)var1 = 0;
		}
		var1 += 4;
	} while (var1 != 0x5ad9b10);
}
