#include "decls.h"
#include <new>
extern struct task *DAT_05edd91c;

// FUNCTION: SADX 0x005fb820
void FUN_005fb820()
{
	*(int *)((char *)DAT_05edd91c->awp + 4) = 0xe;
}

// STUB: SADX 0x005fba20
void FUN_005fba20(int param_1, int *param_2, int *param_3)
{
}

// STUB: SADX 0x005fba70
void *FUN_005fba70(unsigned long size)
{
	return (void *)0;
}

// STUB: SADX 0x005fbae0
int __fastcall FUN_005fbae0(int *param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x005fbb40
void FUN_005fbb40()
{
	ghSetPvrTexMaterial(0xffffffff);
}
