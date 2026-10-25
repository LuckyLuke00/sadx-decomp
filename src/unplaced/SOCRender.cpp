#include "decls.h"
#include <new>
void FUN_004207b0(void);
void UnknowTochar(char *param_1, unsigned long param_2);
extern unsigned char DAT_05ab4243;

// STUB: SADX 0x004198d0
int SOCGetInputLayout(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00419ac0
void __fastcall FUN_00419ac0(void *param_1, int param_2, int param_3)
{
	*(int *)((char *)param_1 + 0x18) = param_3;
	DAT_05ab4243 = 0;
}

// STUB: SADX 0x00419ae0
void __fastcall FUN_00419ae0(void *param_1, void *param_2)
{
}

// FUNCTION: SADX 0x00419b00
void __fastcall FUN_00419b00(void *param_1, float param_2)
{
	*(float *)((char *)param_1 + 0x14) = param_2;
	DAT_05ab4243 = 0;
}

// FUNCTION: SADX 0x00419b20
void __fastcall FUN_00419b20(int param_1, float param_2)
{
	*(float *)(param_1 + 0x10) = param_2;
	DAT_05ab4243 = 0;
}

// FUNCTION: SADX 0x00419b40
void __fastcall FUN_00419b40(float param_1, void *param_2)
{
	*(float *)((char *)param_2 + 0xc) = param_1;
	DAT_05ab4243 = 0;
}

// STUB: SADX 0x00419d00
void __fastcall FUN_00419d00(int param_1, int param_2)
{
}

// STUB: SADX 0x00419d40
void __fastcall FUN_00419d40(int param_1, float param_2)
{
}

// STUB: SADX 0x00419d80
void __fastcall FUN_00419d80(int param_1, int param_2)
{
}

// STUB: SADX 0x0041a170
void UnknowTochar(char *param_1, unsigned long param_2)
{
}

// STUB: SADX 0x0041a1c0
void SOCsetZwrite(bool param_1)
{
}

// STUB: SADX 0x0041a1e0
bool SOCGetZwrite(void)
{
	return (bool)0;
}

// STUB: SADX 0x0041ca20
void FUN_0041ca20(void *param_1, void *param_2, void *param_3)
{
}

// STUB: SADX 0x0041ca60
void FUN_0041ca60(void *param_1, void *param_2, void *param_3)
{
}

// FUNCTION: SADX 0x0041caa0
void __fastcall FUN_0041caa0(int *param_1)
{
	if (param_1[0])
	{
		operator delete((void *)param_1[0]);
	}
	param_1[0] = 0;
	param_1[1] = 0;
	param_1[2] = 0;
}

// STUB: SADX 0x0041cc20
void __fastcall FUN_0041cc20(int param_1)
{
}

// STUB: SADX 0x0041cf30
void __fastcall FUN_0041cf30(void *param_1, void *param_2)
{
}

// STUB: SADX 0x0041cfb0
void __fastcall FUN_0041cfb0(void *param_1, void *param_2)
{
}

// STUB: SADX 0x0041d020
void __fastcall FUN_0041d020(int param_1, int param_2)
{
}

// STUB: SADX 0x0041d130
void __fastcall FUN_0041d130(void *param_1, void *param_2)
{
}

// STUB: SADX 0x0041ddb0
void __fastcall FUN_0041ddb0(int *param_1, int param_2)
{
}

// STUB: SADX 0x0041e270
void __fastcall FUN_0041e270(void *param_1, void *param_2)
{
}

// STUB: SADX 0x004204d0
void __fastcall FUN_004204d0(int *param_1, int param_2)
{
}

// STUB: SADX 0x004207b0
void FUN_004207b0(void)
{
}

// STUB: SADX 0x004207c0
void FUN_004207c0(void)
{
}

// FUNCTION: SADX 0x00421180
void DrawStringW(int param_1, int param_2, const wchar_t *param_3, int param_4, float param_5)
{
	FUN_004208c0(param_1, param_2, param_3, param_4, param_5, 0.0f);
}
