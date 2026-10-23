#include "decls.h"
#include <new>
void * __fastcall FUN_0040cf10(unsigned int param_1);
void FUN_0040c3a0(int param_1);

// STUB: SADX 0x0040c300
void __fastcall FUN_0040c300(void *ptr, int dummy, int free_flag)
{
}

// STUB: SADX 0x0040c3a0
void FUN_0040c3a0(int param_1)
{
}

// STUB: SADX 0x0040c3e0
void FUN_0040c3e0(int *param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0040c470
void * __stdcall FUN_0040c470(void *param_1, void *param_2, void *param_3)
{
	return (void *)0;
}

// STUB: SADX 0x0040c4d0
void FUN_0040c4d0(int *param_1, int *param_2, int *param_3, int *param_4)
{
}

// FUNCTION: SADX 0x0040cd40
void __fastcall FUN_0040cd40(int *param_1, int param_2, int param_3)
{
	int iVar1;
	int *piVar2;

	iVar1 = *param_1;
	*param_1 = *(int *)(iVar1 + 8);
	if (*(char *)(*(int *)(iVar1 + 8) + 0x15) == '\0') {
		*(int **)(*(int *)(iVar1 + 8) + 4) = param_1;
	}
	*(int *)(iVar1 + 4) = param_1[1];
	if (param_1 == *(int **)(*(int *)(param_3 + 4) + 4)) {
		*(int *)(*(int *)(param_3 + 4) + 4) = iVar1;
		*(int **)(iVar1 + 8) = param_1;
		param_1[1] = iVar1;
		return;
	}
	piVar2 = (int *)param_1[1];
	if (param_1 == (int *)piVar2[2]) {
		piVar2[2] = iVar1;
		*(int **)(iVar1 + 8) = param_1;
		param_1[1] = iVar1;
		return;
	}
	*piVar2 = iVar1;
	*(int **)(iVar1 + 8) = param_1;
	param_1[1] = iVar1;
	return;
}

// STUB: SADX 0x0040cf10
void * __fastcall FUN_0040cf10(unsigned int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x0040cfa0
void FUN_0040cfa0(void)
{
}

// STUB: SADX 0x0040d120
void * __fastcall FUN_0040d120(unsigned int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x0040d1b0
void FUN_0040d1b0(int *param_1, int *param_2)
{
}

// STUB: SADX 0x0040d280
void FUN_0040d280(int param_1)
{
}

// STUB: SADX 0x0040d360
void __fastcall FUN_0040d360(int *param_1, int param_2, int param_3)
{
}
