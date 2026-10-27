#include "decls.h"
void FUN_0056cc30(int param_1);
extern int DAT_05ccdd28;

// FUNCTION: SADX 0x0056cde0
void FUN_0056cde0(void)
{
	int *local_8 = (int *)&DAT_05ccdd28;
	*(char *)((char *)local_8 + 0x54) = 0;
}

// FUNCTION: SADX 0x0056ce00
void FUN_0056ce00(char param_1, int param_2, float param_3, float param_4, float param_5, int param_6)
{
	int *local_8 = (int *)&DAT_05ccdd28;
	*(char *)((char *)local_8 + 0x01) = param_1;
	*(char *)((char *)local_8 + 0x54) = 1;
	*(float *)((char *)local_8 + 0x58) = param_3;
	*(float *)((char *)local_8 + 0x5c) = param_4;
	*(float *)((char *)local_8 + 0x60) = param_5;
	*(int *)((char *)local_8 + 0x50) = param_6;
	FUN_0056cc30(param_2);
}

// FUNCTION: SADX 0x0056ce50
void FUN_0056ce50(char param_1, int param_2, int param_3, float param_4, float param_5, float param_6, int param_7)
{
	char *local_8;
	local_8 = (char *)&DAT_05ccdd28;
	*(char *)(local_8 + 1) = param_1;
	*(char *)(local_8 + 0x54) = 2;
	*(int *)(local_8 + 0x64) = param_3;
	*(float *)(local_8 + 0x58) = param_4;
	*(float *)(local_8 + 0x5c) = param_5;
	*(float *)(local_8 + 0x60) = param_6;
	*(int *)(local_8 + 0x50) = param_7;
	FUN_0056cc30(param_2);
}
