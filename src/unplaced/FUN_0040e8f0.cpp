#include "decls.h"
#include <stdio.h>
#include <cctype>
#include <new>
#include <exception>
extern void __cdecl operator delete(void *param_1);
void FUN_0040f020(int param_1, int param_2);
void FUN_004160c0(char *param_1, int param_2, char *param_3, char *param_4);
void __stdcall FUN_00415a10(int param_1);
struct FUN_004157e0_node;

// STUB: SADX 0x0040e960
void FUN_0040e960(void)
{
}

// STUB: SADX 0x0040ea20
void FUN_0040ea20(void)
{
}

// STUB: SADX 0x0040eaf0
void FUN_0040eaf0(void *param_1)
{
}

// STUB: SADX 0x0040ec80
void __fastcall FUN_0040ec80(void *param_1, int param_2, int param_3, int param_4, int param_5)
{
}

// STUB: SADX 0x0040ed80
int __fastcall FUN_0040ed80(int *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x0040f020
void __fastcall FUN_0040f020(void *param_1, int param_2)
{
}

// STUB: SADX 0x0040f080
void neExitLibrary(void)
{
}

// STUB: SADX 0x004115b0
void __stdcall FUN_004115b0(void *param_1)
{
}

// STUB: SADX 0x00411750
void __fastcall FUN_00411750(int *param_1)
{
}

// STUB: SADX 0x004117d0
void * __fastcall FUN_004117d0(unsigned int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x00411830
void __fastcall FUN_00411830(int *param_1)
{
}

// STUB: SADX 0x00411ab0
void * __fastcall FUN_00411ab0(unsigned int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x00411de0
void FUN_00411de0(char *param_1, char *param_2, char *param_3)
{
}

// STUB: SADX 0x00411e00
void FUN_00411e00(int param_1, char *param_2, const char *param_3)
{
}

// STUB: SADX 0x004121c0
void __fastcall FUN_004121c0(void *param_1)
{
}

// STUB: SADX 0x00412210
void FUN_00412210(int param_1)
{
}

// FUNCTION: SADX 0x00412230
void __fastcall FUN_00412230(void *param_1)
{
	void *var1 = *(void **)((char *)param_1 + 0x20);
	if (var1 != (void *)0)
	{
		delete var1;
	}
	*(void **)((char *)param_1 + 0x20) = (void *)0;
	*(void **)((char *)param_1 + 0x24) = (void *)0;
	*(void **)((char *)param_1 + 0x28) = (void *)0;
}

// STUB: SADX 0x00412260
char *FUN_00412260(char *param_1)
{
	char *var1;
	int var2;
	var2 = 0;
	var1 = (char *)0x5ab16e4;
	do
	{
		if (*(char **)var1 == param_1)
		{
			return (char *)0x5ab16d8 + var2 * 0x30;
		}
		var1 = var1 + 0x30;
		var2 = var2 + 1;
	} while ((int)var1 < 0x5ab1f24);
	return (char *)0x0;
}

// STUB: SADX 0x00412290
int __fastcall FUN_00412290(void *param_1, int param_2, void *param_3, void *param_4, int param_5)
{
	return (int)0;
}

// STUB: SADX 0x00414350
void __fastcall FUN_00414350(int *param_1)
{
}

// STUB: SADX 0x00414360
void __fastcall FUN_00414360(int *param_1, int param_2)
{
}

// STUB: SADX 0x00414390
void __stdcall FUN_00414390(int param_1, int param_2)
{
}

// STUB: SADX 0x004143b0
void __fastcall FUN_004143b0(int param_1, int param_2)
{
}

// STUB: SADX 0x00414400
void FUN_00414400(int *param_1)
{
}

// STUB: SADX 0x004144b0
void __fastcall FUN_004144b0(void *param_1)
{
}

// STUB: SADX 0x00414570
void __fastcall FUN_00414570(void *param_1, void *param_2, void *param_3)
{
}

// STUB: SADX 0x00414590
int __fastcall FUN_00414590(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x00414600
void __fastcall FUN_00414600(void *param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x00414970
void __fastcall FUN_00414970(int *param_1)
{
}

// STUB: SADX 0x00414d10
void __fastcall FUN_00414d10(void *param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x00415190
void __fastcall FUN_00415190(void *param_1, void *param_2)
{
}

// STUB: SADX 0x004151f0
void __fastcall FUN_004151f0(void *param_1)
{
}

// STUB: SADX 0x00415750
void * __fastcall FUN_00415750(void *param_1)
{
	return (void *)0;
}

// STUB: SADX 0x004157e0
void __fastcall FUN_004157e0(struct FUN_004157e0_node *param_1, FILE *param_2, int param_3)
{
}

// STUB: SADX 0x00415820
void __fastcall FUN_00415820(void *param_1, void *param_2)
{
}

// FUNCTION: SADX 0x004159d0
void __fastcall FUN_004159d0(void *param_1, int param_2, FILE *param_3, int param_4)
{
	if (param_4 > 0)
	{
		do
		{
			fprintf(param_3, "    ");
			param_4--;
		}
		while (param_4 != 0);
	}
	fprintf(param_3, "<!--%s-->", *(char **)((char *)param_1 + 0x20) + 8);
}

// STUB: SADX 0x00415a10
void __stdcall FUN_00415a10(int param_1)
{
}

// STUB: SADX 0x00415bb0
void __stdcall FUN_00415bb0(int param_1)
{
}

// STUB: SADX 0x00415ef0
void __stdcall FUN_00415ef0(int param_1)
{
}

// STUB: SADX 0x00415f10
void __fastcall FUN_00415f10(void *param_1)
{
}

// FUNCTION: SADX 0x00415f70
void __fastcall FUN_00415f70(void *param_1, int param_2, FILE *param_3, int param_4)
{
	if (param_4 > 0)
	{
		do
		{
			fprintf(param_3, "    ");
			param_4--;
		}
		while (param_4 != 0);
	}
	fprintf(param_3, "<%s>", *(char **)((char *)param_1 + 0x20) + 8);
}

// STUB: SADX 0x00415fb0
void __stdcall FUN_00415fb0(int param_1)
{
}

// STUB: SADX 0x004160c0
void FUN_004160c0(char *param_1, int param_2, char *param_3, char *param_4)
{
}

// FUNCTION: SADX 0x004160e0
int FUN_004160e0(char param_1)
{
	if (isspace((unsigned char)param_1) || param_1 == '\n' || param_1 == '\r')
		return 1;
	return 0;
}
