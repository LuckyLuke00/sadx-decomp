#include "decls.h"
int FUN_00593920(void);

// STUB: SADX 0x00593920
int FUN_00593920()
{
	return (int)0;
}

// FUNCTION: SADX 0x005939b0
void FUN_005939b0(short *param_1, int param_2, short param_3)
{
	if (*(short *)((char *)param_1 + param_2 * 6 + 0xdc) < param_3)
	{
		*(short *)((char *)param_1 + param_2 * 6 + 0xe0) = *(short *)((char *)param_1 + param_2 * 6 + 0xde);
		*(short *)((char *)param_1 + param_2 * 6 + 0xde) = *(short *)((char *)param_1 + param_2 * 6 + 0xdc);
		*(short *)((char *)param_1 + param_2 * 6 + 0xdc) = param_3;
	}
	else if (*(short *)((char *)param_1 + param_2 * 6 + 0xde) < param_3)
	{
		*(short *)((char *)param_1 + param_2 * 6 + 0xe0) = *(short *)((char *)param_1 + param_2 * 6 + 0xde);
		*(short *)((char *)param_1 + param_2 * 6 + 0xde) = param_3;
	}
	else if (*(short *)((char *)param_1 + param_2 * 6 + 0xe0) < param_3)
	{
		*(short *)((char *)param_1 + param_2 * 6 + 0xe0) = param_3;
	}
}

// FUNCTION: SADX 0x00593ab0
void FUN_00593ab0(short *param_1, int param_2, short param_3, short param_4)
{
	if (*(short *)((char *)param_1 + param_2 * 4 + 0xf4) < param_3)
	{
		*(short *)((char *)param_1 + param_2 * 4 + 0xf4) = param_3;
		*(short *)((char *)param_1 + param_2 * 4 + 0xf6) = param_4;
	}
}

// STUB: SADX 0x00593af0
float FUN_00593af0(void)
{
	return (float)0;
}

// STUB: SADX 0x00593b30
float FUN_00593b30(float param_1, int param_2)
{
	return (float)0;
}
