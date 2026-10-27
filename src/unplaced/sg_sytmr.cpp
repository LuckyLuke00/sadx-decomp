#include "decls.h"
#include <windows.h>
extern int DAT_05ad95b8;
extern int DAT_05ad95bc;
extern int DAT_05ad95c0;
extern int DAT_05ad95c8;
extern int DAT_05ad95cc;
extern int DAT_05ad95d4;
extern int DAT_05ad95c4;
extern int DAT_05ad95d8;

// FUNCTION: SADX 0x00423060
void syTmrInit(void)
{
	DAT_05ad95d8 = 0;
	DAT_05ad95b8 = 0;
	DAT_05ad95bc = 0;
	DAT_05ad95c4 = 0;
	DAT_05ad95c8 = 0;
	QueryPerformanceFrequency((LARGE_INTEGER *)&DAT_05ad95cc);
	DAT_05ad95c0 = 0;
	DAT_05ad95d4 = 0;
}

// STUB: SADX 0x004230e0
int syTmrDiffCount(int param_1, int param_2)
{
	return (int)0;
}

// FUNCTION: SADX 0x004230f0
int FUN_004230f0(int param_1)
{
	return param_1;
}

// FUNCTION: SADX 0x00423100
void syTmrGenStart(void)
{
	DAT_05ad95d8 = 1;
	QueryPerformanceCounter((LARGE_INTEGER *)&DAT_05ad95b8);
}

// FUNCTION: SADX 0x00423120
void syTmrGenStop(void)
{
	DAT_05ad95d8 = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&DAT_05ad95c4);
}
