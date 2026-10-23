#include "decls.h"
extern char DAT_060cb334;

// FUNCTION: SADX 0x00717df0
int FUN_00717df0()
{
	return DAT_060cb334;
}

// FUNCTION: SADX 0x00717e00
void FUN_00717e00(int param_1)
{
	dsStop_id(*((int *)(*(int *)(param_1 + 0x20) + 0x10)));
}

// STUB: SADX 0x00717e20
void FUN_00717e20(int param_1)
{
}

// STUB: SADX 0x00717eb0
struct task *FUN_00717eb0(int param_1, int param_2)
{
	return (struct task *)0;
}
