#include "decls.h"
#include <windows.h>
extern int DAT_05ad95c4;
extern int DAT_05ad95d8;

// STUB: SADX 0x00423060
void syTmrInit(void)
{
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

// FUNCTION: SADX 0x00423120
void syTmrGenStop(void)
{
	DAT_05ad95d8 = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&DAT_05ad95c4);
}
