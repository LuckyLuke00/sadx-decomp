#include "decls.h"
extern long DAT_060cd250[4];

// FUNCTION: SADX 0x007e4b90
void CartDataSetSubTotalTime(signed char lap, long time)
{
	DAT_060cd250[lap] = time;
}

// FUNCTION: SADX 0x007e4bb0
void CartDataSetLapTime(signed char lap, long time)
{
	DAT_060cd250[lap + 3] = time;
}

// STUB: SADX 0x007e4c10
int FUN_007e4c10(struct BEST3_CART *param_1)
{
	return (int)0;
}
