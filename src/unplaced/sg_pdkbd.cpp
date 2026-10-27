#include "decls.h"
extern int DAT_01c6eea0[4];
extern int DAT_05ada1d0;

// FUNCTION: SADX 0x00432550
int *pdKbdGetData(int param_1)
{
	int *var2;
	int var1;
	var2 = &DAT_01c6eea0[0];
	var1 = 0;
	do
	{
		if (*var2 == param_1)
		{
			return (int *)&DAT_05ada1d0 + var1 * 3;
		}
		var1++;
		var2++;
	} while (var1 != 4);
	return 0;
}
