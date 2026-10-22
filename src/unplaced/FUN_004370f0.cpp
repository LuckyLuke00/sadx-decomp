#include "decls.h"

// FUNCTION: SADX 0x00437110
unsigned int __fastcall FUN_00437110(unsigned int param_1)
{
	unsigned int uVar1;

	uVar1 = param_1 & 0xf;
	return (uVar1 << 4) | uVar1;
}

// FUNCTION: SADX 0x00437120
unsigned long __fastcall FUN_00437120(unsigned long param_1)
{
	return ((param_1 & 0x1f) * 8) | ((param_1 >> 2) & 7);
}

// FUNCTION: SADX 0x00437140
unsigned int __fastcall FUN_00437140(unsigned int param_1)
{
	return (param_1 & 0x3f) * 4 | (param_1 >> 4) & 3;
}
