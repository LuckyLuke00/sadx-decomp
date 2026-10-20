#include "decls.h"
extern unsigned long DAT_05b3e308[16];
extern int DAT_05bb00a8;
extern int DAT_05cc8670;
extern int DAT_05cc8674;
extern int DAT_05b3e320[16];
extern void (*DAT_05b9e0b0)();

// FUNCTION: SADX 0x004cde50
void ReleaseModule(unsigned long u32ModuleType)
{
	if (u32ModuleType == 0)
	{
		ReleaseSetFile();
		ReleaseCamFile();
	}
	if (u32ModuleType == 5)
	{
		if (DAT_05b9e0b0 == ReleaseMissionObject)
		{
			return;
		}
	}
	if (DAT_05b9e0b0 != 0)
	{
		(*DAT_05b9e0b0)();
	}
	DAT_05b9e0b0 = 0;
}

// FUNCTION: SADX 0x004ce3a0
void ReleaseSetFile()
{
	unsigned int local_8;

	___OutputDebugString("ReleaseSetFile\n");
	DAT_05cc8670 = 0;
	DAT_05cc8674 = 0;
	for (local_8 = 0; local_8 <= 5; local_8++)
	{
		if (DAT_05b3e320[local_8] != 0)
		{
			syFree((void *)DAT_05b3e320[local_8]);
			DAT_05b3e320[local_8] = 0;
		}
	}
}

// FUNCTION: SADX 0x004ce420
char *GetFnamesPlayerStr()
{
	if (*(unsigned char *)&DAT_05bb00a8)
	{
		return last_initial;
	}
	else
	{
		return characterinitial[GetPlayerNumber()];
	}
}

// FUNCTION: SADX 0x004ce450
void ReleaseCamFile()
{
	unsigned int local_8;

	___OutputDebugString("ReleaseCamFile\n");
	for (local_8 = 0; local_8 <= 5; local_8++)
	{
		if (DAT_05b3e308[local_8] != 0)
		{
			syFree((void *)DAT_05b3e308[local_8]);
			DAT_05b3e308[local_8] = 0;
		}
	}
}

// FUNCTION: SADX 0x004cfb60
long NeonuLoadTexture(struct NJS_TEXLIST *pTexlist)
{
	*(char *)((char *)DAT_05b3e320 + 0x28) = 1;
	return njLoadTexture(pTexlist);
}
