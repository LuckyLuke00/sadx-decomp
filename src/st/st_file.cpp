#include "decls.h"
extern void stFileServer(void);
void stReadFileReq(int param_1, int param_2, int param_3, int param_4);
int FUN_00928740();

// STUB: SADX 0x004353b0
void stInitFile(unsigned int param_1)
{
}

// FUNCTION: SADX 0x00435420
int FUN_00435420()
{
	return FUN_00928740();
}

// FUNCTION: SADX 0x00435430
int stGetFileSize(int *param_1)
{
	if (param_1 != 0 && *param_1 != 0)
	{
		return *(int *)((char *)param_1 + 0x1c);
	}
	return 0;
}

// STUB: SADX 0x00435450
void stReadFileReq(int param_1, int param_2, int param_3, int param_4)
{
}

// STUB: SADX 0x004354d0
void stFileServer(void)
{
}

// STUB: SADX 0x00435590
void stReadFile(int param_1, int param_2, int param_3, int param_4)
{
}

// STUB: SADX 0x004355f0
void stCloseFile(int param_1)
{
}

// STUB: SADX 0x00435650
void stFinishFile(void)
{
}
