#include "decls.h"
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern char DAT_05b288ab[5];
extern char DAT_05b289d3;
extern char DAT_05b289d2;
extern char DAT_05b288a8[];
extern char DAT_05b289d1;
extern char DAT_05b289d4;
extern char DAT_05b288a8[1];
extern char DAT_05b288b0[5];
extern char DAT_05b288b0[];

// FUNCTION: SADX 0x00443af0
void AL_InitRaceInfo()
{
	int var1;
	void *var2;

	memset(DAT_05b288a8, 0, 0x4130);
	var2 = (void *)FUN_0043f310();
	memcpy(DAT_05b288a8, var2, 0x126);
	if (AL_GetStageNumber() - 1 == 0)
	{
		for (var1 = 0; var1 < 8; var1++)
		{
			AL_SetSelectedChaoSaveInfo(var1, 0);
		}
	}
}

// FUNCTION: SADX 0x00443b40
struct AL_RACE_INFO *AL_GetRaceInfo()
{
	return (struct AL_RACE_INFO *)DAT_05b288a8;
}

// FUNCTION: SADX 0x00443b50
long AL_ClearnbPlayer()
{
	DAT_05b289d4 = 0;
	return 0;
}

// FUNCTION: SADX 0x00443b60
long AL_IncnbPlayer()
{
	DAT_05b289d4 += 1;
	if (DAT_05b289d1 == 2)
		return (long)DAT_05b289d4;
	return 1;
}

// FUNCTION: SADX 0x00443b80
long AL_GetnbPlayer()
{
	long var1 = 1;
	if (DAT_05b289d1 == 2)
		var1 = (long)(char)DAT_05b289d4;
	return var1;
}

// FUNCTION: SADX 0x00443ba0
void AL_SetRaceNew(enum eRaceNum num)
{
	if ((unsigned int)num <= 2 && DAT_05b288a8[num] == 0)
	{
		DAT_05b288a8[num] = 2;
	}
}

// FUNCTION: SADX 0x00443bc0
void AL_SetRacePlayed(enum eRaceNum num)
{
	if ((unsigned int)num <= 2)
	{
		DAT_05b288a8[num] = 3;
	}
}

// FUNCTION: SADX 0x00443be0
enum eRACE_ACTIVE_FLAG AL_GetRaceActiveFlag(enum eRaceNum num)
{
	return (enum eRACE_ACTIVE_FLAG)(char)DAT_05b288a8[(int)num];
}

// FUNCTION: SADX 0x00443bf0
void AL_SetRaceNum(enum eRaceNum num)
{
	DAT_05b289d1 = (char)num;
}

// FUNCTION: SADX 0x00443c00
enum eRaceNum AL_GetRaceNum()
{
	return (enum eRaceNum)DAT_05b289d1;
}

// FUNCTION: SADX 0x00443c10
void AL_SetCourseNum(enum eCourseNumDX num)
{
	DAT_05b289d2 = (char)num;
}

// FUNCTION: SADX 0x00443c20
enum eCourseNumDX AL_GetCourseNum()
{
	return (enum eCourseNumDX)DAT_05b289d2;
}

// FUNCTION: SADX 0x00443c30
void AL_SetCourseLevel(long num)
{
	DAT_05b289d3 = (char)num;
}

// FUNCTION: SADX 0x00443c40
long AL_GetCourseLevel()
{
	return (long)(char)DAT_05b289d3;
}

// FUNCTION: SADX 0x00443c50
void AL_SetCourseChallengedLevel(enum eCourseNumDX num, long lev)
{
	int var1;
	long var2;

	var1 = (int)num;
	var2 = lev;
	if (var2 <= (long)(char)DAT_05b288ab[var1])
		return;
	if (var1 < 0)
		return;
	if (var1 > 4)
		return;
	if (var2 > 5)
		return;
	DAT_05b288ab[var1] = (char)var2;
}

// FUNCTION: SADX 0x00443c80
long AL_GetCourseClearedLevel(enum eCourseNumDX num)
{
	return (long)(char)DAT_05b288b0[num];
}

// FUNCTION: SADX 0x00443c90
void AL_CourseClearedLevelUp(enum eCourseNumDX num)
{
	int var1;

	var1 = (int)num;
	if (var1 < 0)
		return;
	if (var1 > 4)
		return;
	if (DAT_05b288b0[var1] >= 5)
		return;
	DAT_05b288b0[var1] += 1;
}

// STUB: SADX 0x00443cb0
void AL_GetCourseRecord(enum eCourseNumDX num, struct AL_RECORD *pRecord)
{
}

// STUB: SADX 0x00443ce0
void AL_SetCourseRecord(enum eCourseNumDX num, struct AL_RECORD *pRecord)
{
}
