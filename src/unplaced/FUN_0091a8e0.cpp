#include "decls.h"
extern unsigned char (*z80_op_dd_cb[256])(void);
unsigned char FUN_0090ccb0(int param_1);
extern char *DAT_060ee5b8;

// FUNCTION: SADX 0x0091a8e0
void FUN_0091a8e0()
{
	int var1;
	int var2;

	var1 = FUN_0090ccb0((unsigned short)(*(short *)((char *)DAT_060ee5b8 + 0x20) + 1));
	var2 = var1 & 0xff;
	z80_op_dd_cb[var2]();
	*(short *)((char *)DAT_060ee5b8 + 0x20) = *(short *)((char *)DAT_060ee5b8 + 0x20) + 2;
}

// STUB: SADX 0x0091a910
void FUN_0091a910()
{
}

// FUNCTION: SADX 0x0091a940
void FUN_0091a940()
{
	*(short *)(DAT_060ee5b8 + 0x20) = *(short *)(DAT_060ee5b8 + 0x20) + 1;
}
