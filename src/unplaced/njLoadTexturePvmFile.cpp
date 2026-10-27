#include "decls.h"

// FUNCTION: SADX 0x0067ec20
void njSetPvmTextureList(int *param_1, int *param_2, int param_3, int param_4)
{
	if (param_4 > 0)
	{
		int *piVar1 = param_2;
		do
		{
			*piVar1 = param_3;
			param_3 = param_3 + 0x1c;
			param_4 = param_4 + -1;
			piVar1 = piVar1 + 3;
		}
		while (param_4 != 0);
		*param_1 = (int)param_2;
		return;
	}
	*param_1 = (int)param_2;
	return;
}
