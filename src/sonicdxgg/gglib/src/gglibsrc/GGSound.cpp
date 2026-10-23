#include "decls.h"
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);

// FUNCTION: SADX 0x0090bcf0
int FUN_0090bcf0()
{
	return 0x49580;
}

// FUNCTION: SADX 0x0090bd00
void __fastcall FUN_0090bd00(int param_1)
{
	if (*(int *)(param_1 + 0x90) != 0 && *(int *)(param_1 + 0x94) != 0)
	{
		delete *(void **)(param_1 + 0x94);
		*(int *)(param_1 + 0x94) = 0;
	}
}

// FUNCTION: SADX 0x0090c080
void __fastcall FUN_0090c080(void *param_1)
{
	*(double *)((char *)param_1 + 0x11620) = 0.0;
	*(int *)((char *)param_1 + 0x2c) = 0;
	*(int *)((char *)param_1 + 0x28) = 0;
	*(int *)((char *)param_1 + 0x24) = 0;
	*(int *)((char *)param_1 + 0x60) = 0;
	*(int *)((char *)param_1 + 0x5c) = 0;
	*(int *)((char *)param_1 + 0x58) = 0;
	*(int *)((char *)param_1 + 0x54) = 0;
	*(int *)((char *)param_1 + 0x50) = 0;
	*(int *)((char *)param_1 + 0x4c) = 0;
	*(int *)((char *)param_1 + 0x38) = 0xf;
	*(int *)((char *)param_1 + 0x34) = 0xf;
	*(int *)((char *)param_1 + 0x30) = 0xf;
	*(int *)((char *)param_1 + 0x3c) = 0x10000;
	*(int *)((char *)param_1 + 0x40) = 0;
	*(int *)((char *)param_1 + 0x44) = 1;
	*(int *)((char *)param_1 + 0x48) = 0xf;
	*(int *)((char *)param_1 + 0x64) = 0;
	*(int *)((char *)param_1 + 0x68) = 0x37f1;
	*(int *)((char *)param_1 + 0x6c) = 0;
	*(int *)((char *)param_1 + 0x74) = 0;
	*(int *)((char *)param_1 + 0x11628) = 0;
}

// FUNCTION: SADX 0x0090cc20
void __fastcall FUN_0090cc20(int param_1)
{
	FUN_0090c080((void *)param_1);
	*(int *)(param_1 + 0x85cc) = 0;
	memset((void *)(param_1 + 0x5cc), 0, 0x8000);
}
