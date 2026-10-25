#include "decls.h"
extern void FUN_00418a70(void);
extern void FUN_0094bac0(void);
extern int DAT_0629c200;
extern int DAT_062994b8;

// STUB: SADX 0x00418940
int * FUN_00418940(void)
{
	return (int *)0;
}

// STUB: SADX 0x00418990
void FUN_00418990(void *param_1, int param_2)
{
}

// STUB: SADX 0x004189f0
void FUN_004189f0(int param_1)
{
}

// STUB: SADX 0x00418a00
void __fastcall FUN_00418a00(int param_1)
{
}

// FUNCTION: SADX 0x00418a40
int FUN_00418a40(void)
{
	if ((DAT_0629c200 & 1) == 0)
	{
		DAT_0629c200 |= 1;
		FUN_00418a70();
		atexit(FUN_0094bac0);
	}
	return (int)&DAT_062994b8;
}

// STUB: SADX 0x00418b80
void __fastcall FUN_00418b80(void * param_1, int param_2)
{
}

// STUB: SADX 0x00418fc0
void __stdcall FUN_00418fc0(int *param_1)
{
}

// STUB: SADX 0x004190a0
void __fastcall FUN_004190a0(int param_1, int param_2, int param_3, int param_4)
{
}

// FUNCTION: SADX 0x004190c0
int FUN_004190c0(void)
{
	return 0x10;
}

// STUB: SADX 0x004190d0
void FUN_004190d0(void *param_1)
{
}

// FUNCTION: SADX 0x004190e0
int FUN_004190e0(void)
{
	return 0x98;
}

// STUB: SADX 0x004190f0
void * __fastcall FUN_004190f0(void *param_1, int param_2)
{
	return (void *)0;
}
