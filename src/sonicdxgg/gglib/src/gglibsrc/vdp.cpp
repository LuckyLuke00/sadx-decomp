#include "decls.h"
extern char DAT_04cbb1e0[11];

// FUNCTION: SADX 0x0091b1b0
void __fastcall FUN_0091b1b0(int param_1)
{
	int var1;
	for (var1 = 0; var1 < 0xb; var1++)
	{
		*(char *)(param_1 + 4 + var1) = DAT_04cbb1e0[var1];
	}
}

// FUNCTION: SADX 0x0091b1d0
int __fastcall FUN_0091b1d0(void *param_1)
{
	return (int)((char *)param_1 + 4);
}
