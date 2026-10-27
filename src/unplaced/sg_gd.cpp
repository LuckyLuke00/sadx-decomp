#include "decls.h"
void gdFsExecServer(void);
void stCloseFile(int param_1);
void stReadFile(int param_1, int param_2, int param_3, int param_4);

// STUB: SADX 0x004310d0
int gdFsOpen(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00431150
int gdFsRead(int param_1, int param_2, int param_3)
{
	int var1;

	if (param_1 != 0 && param_3 != 0 && *(short *)(param_1 + 0x4c) != 0)
	{
		var1 = param_2 << 0xb;
		stReadFile(*(int *)param_1, param_3, *(int *)(param_1 + 0x14), var1);
		*(int *)(param_1 + 0x14) += var1;
		if (*(int *)(param_1 + 0xc) < *(int *)(param_1 + 0x14))
		{
			*(int *)(param_1 + 0x14) = *(int *)(param_1 + 0xc);
		}
		return 0;
	}
	return -10;
}

// FUNCTION: SADX 0x004311a0
int gdFsGetFileSctSize(void *param_1, int *param_2)
{
	if ((param_1 != 0) && (*(short *)((char *)param_1 + 0x4c) != 0))
	{
		*param_2 = *(int *)((char *)param_1 + 0x10);
		return 1;
	}
	return 0;
}

// STUB: SADX 0x004311d0
void gdFsExecServer(void)
{
}

// FUNCTION: SADX 0x004311f0
void gdHandleInit(int *param_1)
{
	if (param_1 != 0)
	{
		param_1[0] = 0;
		param_1[1] = 0;
		param_1[2] = 0;
		param_1[3] = 0;
		param_1[4] = 0;
		param_1[5] = 0;
		param_1[6] = 0;
		param_1[7] = 0;
		param_1[8] = 0;
		param_1[9] = 0;
		param_1[10] = 0;
		param_1[11] = 0;
		param_1[12] = 0;
		param_1[13] = 0;
		param_1[14] = 0;
		param_1[15] = 0;
		param_1[16] = 0;
		param_1[17] = 0;
		param_1[18] = 0;
		param_1[19] = 0;
		param_1[20] = 0xffe50000;
	}
}

// FUNCTION: SADX 0x00431240
void gdFsClose(int *param_1)
{
	if (param_1)
	{
		if (*(short *)((char *)param_1 + 0x4c) != 0)
		{
			stCloseFile(*param_1);
		}
		gdHandleInit(param_1);
	}
}

// STUB: SADX 0x00431410
void gdFsFinish(void)
{
}
