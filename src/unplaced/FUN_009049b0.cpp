#include "decls.h"

// FUNCTION: SADX 0x009049b0
void FUN_009049b0(void **param_1, unsigned int param_2)
{
	unsigned int var1;
	int *var2;

	var1 = param_2 >> 3;
	if (var1 != 0)
	{
		var2 = (int *)param_1 + var1 * 2 + 1;
		do
		{
			var2 -= 2;
			if (*var2 != 0)
			{
				((void (*)(void))*var2)();
			}
			var1--;
		} while (var1 != 0);
	}
}
