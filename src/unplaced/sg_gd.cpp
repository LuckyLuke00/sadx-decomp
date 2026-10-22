#include "decls.h"
void stCloseFile(int param_1);
void stReadFile(int param_1, int param_2, int param_3, int param_4);

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

// STUB: SADX 0x004311f0
void gdHandleInit(int *param_1)
{
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
