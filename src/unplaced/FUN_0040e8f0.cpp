#include "decls.h"
#include <stdio.h>
#include <cctype>
void FUN_004160c0(char *param_1, int param_2, char *param_3, char *param_4);
void __stdcall FUN_00415a10(int param_1);
struct FUN_004157e0_node;

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
	return (char *)0;
}

// STUB: SADX 0x00414350
void __fastcall FUN_00414350(int *param_1)
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

// STUB: SADX 0x00414570
void __fastcall FUN_00414570(void *param_1, void *param_2, void *param_3)
{
}

// STUB: SADX 0x00414590
int __fastcall FUN_00414590(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x00414970
void __fastcall FUN_00414970(int *param_1)
{
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

// STUB: SADX 0x00415f70
void __fastcall FUN_00415f70(void *param_1, int param_2, FILE *param_3)
{
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
