#include "decls.h"
void stCloseFile(int param_1);
void stReadFile(int param_1, int param_2, int param_3, int param_4);

// STUB: SADX 0x004310d0
int gdFsOpen(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00431150
int gdFsRead(int gdfs, int nsct, int buf)
{
	int var1;

	if (gdfs != 0 && buf != 0 && *(short *)(gdfs + 0x4c) != 0)
	{
		var1 = nsct << 0xb;
		stReadFile(*(int *)gdfs, buf, *(int *)(gdfs + 0x14), var1);
		*(int *)(gdfs + 0x14) += var1;
		if (*(int *)(gdfs + 0xc) < *(int *)(gdfs + 0x14))
		{
			*(int *)(gdfs + 0x14) = *(int *)(gdfs + 0xc);
		}
		return 0;
	}
	return -10;
}

// FUNCTION: SADX 0x004311a0
int gdFsGetFileSctSize(void *gdfs, int *fsctsize)
{
	if ((gdfs != 0) && (*(short *)((char *)gdfs + 0x4c) != 0))
	{
		*fsctsize = *(int *)((char *)gdfs + 0x10);
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
void gdFsClose(int *gdfs)
{
	if (gdfs)
	{
		if (*(short *)((char *)gdfs + 0x4c) != 0)
		{
			stCloseFile(*gdfs);
		}
		gdHandleInit(gdfs);
	}
}

// STUB: SADX 0x00431410
void gdFsFinish(void)
{
}
