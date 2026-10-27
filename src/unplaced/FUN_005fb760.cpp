#include "decls.h"
#include <new>
extern struct task *DAT_05edd91c;

// STUB: SADX 0x005fb760
void FUN_005fb760()
{
}

// FUNCTION: SADX 0x005fb820
void FUN_005fb820()
{
	*(int *)((char *)DAT_05edd91c->awp + 4) = 0xe;
}

// STUB: SADX 0x005fba20
void FUN_005fba20(int param_1, int *param_2, int *param_3)
{
}

// FUNCTION: SADX 0x005fba70
void *FUN_005fba70(unsigned long param_1, int param_2)
{
	void *local_8 = 0;
	if (param_1 <= 0)
	{
		param_1 = 0;
	}
	else if (param_1 > 0x234f72c || (local_8 = operator new(param_1 * 0x74)) == 0)
	{
		throw std::bad_alloc(0);
	}
	return local_8;
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
