#include "decls.h"
extern char DAT_02631488[1];
extern char DAT_02631494[16];
extern int DAT_05b3ebbc;

// FUNCTION: SADX 0x005a3e60
char FUN_005a3e60(int param_1)
{
	char local_5;
	local_5 = (char)(param_1 & 0xff);
	if ((unsigned int)(param_1 & 0x1ff) >= 0x100)
	{
		local_5 = (char)(0xff - local_5);
	}
	return local_5;
}

// FUNCTION: SADX 0x005a3ea0
void FUN_005a3ea0(int param_1)
{
	DialogJimakuInit();
	DialogJimakuPut(*(char **)(*(char **)(DAT_02631488 + *(char *)(param_1 + 0x14) * 4) + DAT_05b3ebbc * 4));
}

// FUNCTION: SADX 0x005a3ed0
void FUN_005a3ed0(int param_1)
{
	DialogJimakuInit();
	DialogJimakuPut(*(char **)(*(char **)(DAT_02631494 + *(char *)(param_1 + 0x14) * 4) + DAT_05b3ebbc * 4));
}

// FUNCTION: SADX 0x005a3f00
void FUN_005a3f00(int param_1)
{
	DialogJimakuInit();
	DialogJimakuPut(*(char **)(*(char **)(DAT_02631494 + 8 + *(char *)(param_1 + 0x14) * 4) + DAT_05b3ebbc * 4));
}
