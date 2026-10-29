#include "decls.h"
extern int DAT_01c6eea0[4];
extern struct PDS_PERIPHERAL DAT_05ad9db8[4];

// FUNCTION: SADX 0x00430e60
void *pdGetPeripheral(int param_1)
{
	int var1;
	int *var2;
	var2 = &DAT_01c6eea0[0];
	var1 = 0;
	do
	{
		if (*var2 == param_1)
		{
			return &DAT_05ad9db8[var1];
		}
		var1++;
		var2++;
	} while (var1 != 4);
	return 0;
}
