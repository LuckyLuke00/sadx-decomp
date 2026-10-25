#include "decls.h"
extern char DAT_05b288b0[5];
extern char DAT_05b288b0[];

// STUB: SADX 0x00443b40
struct AL_RACE_INFO *AL_GetRaceInfo()
{
	return (struct AL_RACE_INFO *)0;
}

// STUB: SADX 0x00443ba0
void AL_SetRaceNew(enum eRaceNum num)
{
}

// STUB: SADX 0x00443bc0
void AL_SetRacePlayed(enum eRaceNum num)
{
}

// STUB: SADX 0x00443c50
void AL_SetCourseChallengedLevel(enum eCourseNumDX num, long lev)
{
}

// FUNCTION: SADX 0x00443c80
long AL_GetCourseClearedLevel(enum eCourseNumDX num)
{
	return (long)(char)DAT_05b288b0[num];
}

// STUB: SADX 0x00443c90
void AL_CourseClearedLevelUp(enum eCourseNumDX num)
{
}

// STUB: SADX 0x00443cb0
void AL_GetCourseRecord(enum eCourseNumDX num, struct AL_RECORD *pRecord)
{
}

// STUB: SADX 0x00443ce0
void AL_SetCourseRecord(enum eCourseNumDX num, struct AL_RECORD *pRecord)
{
}
