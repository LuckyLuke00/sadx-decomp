#include "decls.h"
#include <stdio.h>
#include <stdlib.h>
extern "C" void free(void *param_1);
extern void * DAT_05ab25ac;
extern void * DAT_05ab25b0;
extern unsigned int DAT_05ab25b4;
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);
struct FUN_004086f0_004086f0;
void FUN_004086c0(void *param_1, void *param_2);
extern "C" void free(void *param_1);
void __stdcall FUN_00408490(void *param_1, void *param_2, void *param_3, void *param_4);

// FUNCTION: SADX 0x00407f40
void * FUN_00407f40()
{
	void * var1;

	if (DAT_05ab25ac != NULL)
	{
		var1 = DAT_05ab25ac;
		DAT_05ab25ac = *(void **)((char *)var1 + 0xc);
		return var1;
	}

	if (DAT_05ab25b0 == NULL || DAT_05ab25b4 >= 0x200)
	{
		void * var2 = (void *)operator new(0x2004);
		if (var2 != NULL)
		{
			*(int *)((char *)var2 + 0x2000) = 0;
		}
		else
		{
			var2 = NULL;
		}
		*(void **)((char *)var2 + 0x2000) = DAT_05ab25b0;
		DAT_05ab25b0 = var2;
		DAT_05ab25b4 = 0;
	}

	var1 = (char *)DAT_05ab25b0 + DAT_05ab25b4 * 0x10;
	DAT_05ab25b4 = DAT_05ab25b4 + 1;
	return var1;
}

// STUB: SADX 0x00408030
void __fastcall FUN_00408030(void *param_1, char param_2)
{
}

// STUB: SADX 0x00408100
void __stdcall FUN_00408100(void *param_1)
{
}

// STUB: SADX 0x00408230
void __fastcall FUN_00408230(int *param_1)
{
}

// STUB: SADX 0x00408290
void __fastcall FUN_00408290(int *param_1, int param_2)
{
}

// STUB: SADX 0x004083f0
void __fastcall FUN_004083f0(void *param_1, int param_2)
{
}

// STUB: SADX 0x00408410
unsigned char * __fastcall FUN_00408410(int param_1, unsigned char *param_2, unsigned char *param_3)
{
	return (unsigned char *)0;
}

// FUNCTION: SADX 0x00408440
char __stdcall FUN_00408440(char param_1)
{
	return param_1;
}

// FUNCTION: SADX 0x00408450
char *__stdcall FUN_00408450(char *param_1, char *param_2, char *param_3)
{
	memcpy(param_3, param_1, (int)(param_2 - param_1));
	return param_2;
}

// FUNCTION: SADX 0x00408480
char __stdcall FUN_00408480(char param_1, char param_2)
{
	return param_1;
}

// STUB: SADX 0x00408490
void __stdcall FUN_00408490(void *param_1, void *param_2, void *param_3, void *param_4)
{
}

// STUB: SADX 0x004084c0
void FUN_004084c0(void *param_1, int param_2)
{
}

// STUB: SADX 0x00408510
void __fastcall FUN_00408510(void *param_1, int param_2)
{
}

// STUB: SADX 0x004086b0
void FUN_004086b0()
{
}

// STUB: SADX 0x004086c0
void FUN_004086c0(void *param_1, void *param_2)
{
}

// STUB: SADX 0x004086f0
void __fastcall FUN_004086f0(FUN_004086f0_004086f0 *param_1, FUN_004086f0_004086f0 *param_2)
{
}

// STUB: SADX 0x00408720
void __fastcall FUN_00408720(int param_1, int param_2)
{
}

// STUB: SADX 0x004087b0
void FUN_004087b0(void *param_1)
{
}

// STUB: SADX 0x00408810
void __fastcall FUN_00408810(int param_1, char *param_2)
{
}

// FUNCTION: SADX 0x004088d0
void __fastcall FUN_004088d0(void **param_1)
{
	if (*param_1 != (void *)0x0)
	{
		free(*param_1);
	}
	*param_1 = (void *)0x0;
}

// STUB: SADX 0x004088f0
void __fastcall FUN_004088f0(void *param_1)
{
}

// STUB: SADX 0x00408960
void __fastcall FUN_00408960(int param_1)
{
}

// STUB: SADX 0x00408970
void __fastcall FUN_00408970(void *p)
{
}

// STUB: SADX 0x004089f0
void __fastcall FUN_004089f0(int param_1)
{
}

// STUB: SADX 0x00408a00
void __fastcall FUN_00408a00(int param_1)
{
}

// FUNCTION: SADX 0x00408a10
int __stdcall FUN_00408a10(int param_1)
{
	return 0xffffffff;
}

// STUB: SADX 0x00408a20
int FUN_00408a20()
{
	return (int)0;
}

// STUB: SADX 0x00408c20
void __stdcall FUN_00408c20(int *param_1, int *param_2, int *param_3, int *param_4, int *param_5)
{
}

// STUB: SADX 0x00408c50
void __stdcall FUN_00408c50(int *param_1)
{
}

// STUB: SADX 0x00408c80
int __fastcall FUN_00408c80(int param_1, int param_2)
{
	return (int)0;
}
