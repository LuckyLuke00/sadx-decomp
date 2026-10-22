#include "decls.h"

// STUB: SADX 0x00487e70
void FUN_00487e70(short *param_1)
{
}

// FUNCTION: SADX 0x00487e80
void FUN_00487e80(char *param_1, char param_2, char param_3, char param_4)
{
	*param_1 = param_4;
	param_1[1] = param_3;
	param_1[2] = param_2;
	return;
}

// FUNCTION: SADX 0x00487ea0
void FUN_00487ea0(unsigned char *param_1)
{
	*param_1 = *param_1 + 1;
	if (*param_1 >= 0x3c)
	{
		param_1[1] = param_1[1] + 1;
		*param_1 = 0;
	}
	if (param_1[1] >= 0x3c)
	{
		param_1[2] = param_1[2] + 1;
		param_1[1] = 0;
	}
	if (param_1[2] >= 0x64)
	{
		param_1[2] = 0x64;
	}
}
