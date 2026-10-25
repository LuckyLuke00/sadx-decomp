#include "decls.h"
void FUN_0056cc30(int param_1);
extern int DAT_05ccdd28;

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

// STUB: SADX 0x0056ce50
void FUN_0056ce50(char param_1, int param_2, int param_3, int param_4, float param_5, float param_6, float param_7, int param_8)
{
}
