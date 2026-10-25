#include "decls.h"
extern "C" char *strcat(char *param_1, const char *param_2);
extern "C" char *strcpy(char *param_1, const char *param_2);
void LoadSetFile(char *pcFileName, unsigned long u32SetType);
extern unsigned long DAT_05b3e308[16];
extern unsigned char DAT_05bb00a8;
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
	if (DAT_05bb00a8)
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

// STUB: SADX 0x004cf3a0
void LoadSetFile(char *pcFileName, unsigned long u32SetType)
{
}

// FUNCTION: SADX 0x004cf4c0
void LoadCamFile(char *pcFileName, unsigned long u32CamType)
{
	char aFileName[32];
	char *local_8g;

	if (u32CamType == 0)
	{
		ReleaseCamFile();
	}
	local_8g = characterinitial[GetPlayerNumber()];
	strcpy(aFileName, "cam");
	strcat(aFileName, pcFileName);
	strcat(aFileName, local_8g);
	strcat(aFileName, ".bin");
	if (LoadFileWithMalloc(aFileName, (void **)&DAT_05b3e308[u32CamType]) == -1)
	{
		if (DAT_05b3e308[u32CamType] != 0)
		{
			syFree((void *)DAT_05b3e308[u32CamType]);
		}
		local_8g = characterinitial[0];
		strcpy(aFileName, "cam");
		strcat(aFileName, pcFileName);
		strcat(aFileName, local_8g);
		strcat(aFileName, ".bin");
		LoadFileWithMalloc(aFileName, (void **)&DAT_05b3e308[u32CamType]);
	}
}

// STUB: SADX 0x004cf5e0
void LoadPlayerMotionData(long PlayerNo)
{
}

// FUNCTION: SADX 0x004cfb60
long NeonuLoadTexture(struct NJS_TEXLIST *pTexlist)
{
	*(char *)((char *)DAT_05b3e320 + 0x28) = 1;
	return njLoadTexture(pTexlist);
}
