#include "decls.h"
#include <time.h>
extern int DAT_04c7c0c0;

// FUNCTION: SADX 0x00430fc0
long syRtcGetDate(struct _SYS_RTC_DATE *param_1)
{
	__time64_t var1;
	struct tm *var2;

	if (param_1 != NULL)
	{
		_time64(&var1);
		var2 = _localtime64(&var1);
		if (var2 != NULL)
		{
			*(short *)((char *)param_1 + 0) = (short)(var2->tm_year + 0x76c);
			*(char *)((char *)param_1 + 2) = (char)(var2->tm_mon + 1);
			*(char *)((char *)param_1 + 3) = (char)var2->tm_mday;
			*(char *)((char *)param_1 + 4) = (char)var2->tm_hour;
			*(char *)((char *)param_1 + 5) = (char)var2->tm_min;
			*(char *)((char *)param_1 + 6) = (char)var2->tm_sec;
			*(char *)((char *)param_1 + 7) = (char)var2->tm_wday;
			*(char *)((char *)param_1 + 8) = 0;
		}
	}
	return 1;
}

// FUNCTION: SADX 0x00431030
void syRtcDateToCount(struct _SYS_RTC_DATE const *param_1, unsigned long *param_2)
{
	struct tm var1;

	if (param_1 != 0 && param_2 != 0)
	{
		var1.tm_year = *(unsigned short *)param_1 - 0x76c;
		var1.tm_mon = *(unsigned char *)((char *)param_1 + 2) - 1;
		var1.tm_mday = *(unsigned char *)((char *)param_1 + 3);
		var1.tm_hour = *(unsigned char *)((char *)param_1 + 4);
		var1.tm_min = *(unsigned char *)((char *)param_1 + 5);
		var1.tm_sec = *(unsigned char *)((char *)param_1 + 6);
		var1.tm_wday = *(unsigned char *)((char *)param_1 + 7);
		*param_2 = _mktime64(&var1);
	}
}

// FUNCTION: SADX 0x004310b0
long syRtcInit(void)
{
	njEntryWaitVSyncFunc((void (__cdecl *)(void))FUN_007d21b0);
	return 0;
}

// FUNCTION: SADX 0x004310c0
void syRtcFinish(void)
{
	njDeleteWaitVSyncFunc((void (__cdecl *)(void))FUN_007d21b0);
}
