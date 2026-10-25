#include "decls.h"
extern void *DAT_060ce760;

// FUNCTION: SADX 0x007f2250
void MainBGM_Stop()
{
	EndAdvaBGM();
}

// STUB: SADX 0x007f2260
long Expand2(void *src, void *dest)
{
	return (long)0;
}

// FUNCTION: SADX 0x007f2340
void GG_Initialize()
{
	DAT_060ce760 = syMalloc(0x100200);
}

// FUNCTION: SADX 0x007f2360
void GG_Finalize()
{
	if (DAT_060ce760)
	{
		syFree(DAT_060ce760);
		DAT_060ce760 = 0;
	}
}

// FUNCTION: SADX 0x007f2380
void *LoadPrsMallocFile(const char *filename, long *GG_Size)
{
	void *var1;

	var1 = syMalloc(__GetFileSize(filename));
	LoadFile((char *)filename, var1);
	*GG_Size = Expand2(var1, DAT_060ce760);
	syFree(var1);
	return DAT_060ce760;
}
