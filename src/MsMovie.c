#include "decls.h"
extern int DAT_05cda154;
void FUN_004a0520(float param_1, float param_2);

// FUNCTION: SADX 0x0059bd50
long MsMovie(long mn)
{
	long local_8;

	local_8 = 1;
	njWaitVSync();
	FUN_004a0520(-1.0, -2000.0);
	njSetCamera(&DAT_06298c48);
	njSetWaitVsyncCount(1);
	local_8 = movie(mn);
	DAT_05cda154 = 0;
	njWaitVSync();
	return local_8;
}
