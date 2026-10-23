#include "decls.h"
extern int DAT_060cee68;

// STUB: SADX 0x00805600
long NearTornade(struct NJS_POINT3 *pos, float *dist)
{
	return (long)0;
}

// STUB: SADX 0x00805650
long GetTornadePos(struct NJS_POINT3 *pos)
{
	return (long)0;
}

// FUNCTION: SADX 0x008059d0
long TornadeFinish()
{
	return DAT_060cee68 == 1;
}
