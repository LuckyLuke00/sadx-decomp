#include "decls.h"
extern char DAT_02631494[16];
extern int DAT_05b3ebbc;

// STUB: SADX 0x005a3e60
char FUN_005a3e60(char param_1)
{
	return (char)0;
}

// STUB: SADX 0x005a3ea0
void FUN_005a3ea0(int param_1)
{
}

// FUNCTION: SADX 0x005a3ed0
void FUN_005a3ed0(int param_1)
{
	DialogJimakuInit();
	DialogJimakuPut(*(char **)(*(char **)(DAT_02631494 + *(char *)(param_1 + 0x14) * 4) + DAT_05b3ebbc * 4));
}

// STUB: SADX 0x005a3f00
void FUN_005a3f00(int param_1)
{
}
