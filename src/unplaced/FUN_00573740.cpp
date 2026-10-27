#include "decls.h"
extern void FUN_004f5550(int param_1);
extern unsigned char DAT_05bb00a8;
extern int DAT_05cd0f28;
void FUN_004f5550(int param_1);

// FUNCTION: SADX 0x00573740
void FUN_00573740(void)
{
	FUN_004f5550(0xa6);
	FUN_004f5550(0x119);
	if (DAT_05cd0f28 < 0)
	{
		FUN_004f5550(0x189);
	}
	FUN_004f5550(0x1d0);
	DAT_05bb00a8 = 0;
}
