#include "decls.h"
extern char DAT_05edc45c[1];

// STUB: SADX 0x005d55f0
long AmyHndlGetHandleAngle(long *ang)
{
	return (long)0;
}

// STUB: SADX 0x005d5680
struct amyhndlstr *AmyHndlEntryTouchHandle(struct NJS_POINT3 *hndlpos, long hndlangy)
{
	return (struct amyhndlstr *)0;
}

// FUNCTION: SADX 0x005d5770
struct amyhndlstr *AmyHndlGetInfoStrP()
{
	return (struct amyhndlstr *)DAT_05edc45c;
}
