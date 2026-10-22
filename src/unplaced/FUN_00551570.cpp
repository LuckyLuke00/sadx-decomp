#include "decls.h"

// FUNCTION: SADX 0x00551570
int FUN_00551570(int param_1)
{
	return *(short *)((char *)*(int *)(param_1 + 0x1c) + 2) & 4;
}
