#include "decls.h"
extern struct taskwk *DAT_05baf368[8];
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

// FUNCTION: SADX 0x005d5740
int FUN_005d5740()
{
	int local_8;

	local_8 = (int)DAT_05baf368[0];
	if (local_8 == 0 || GetPlayerNumber() != 5)
		return 0;
	return local_8;
}

// FUNCTION: SADX 0x005d5770
struct amyhndlstr *AmyHndlGetInfoStrP()
{
	return (struct amyhndlstr *)DAT_05edc45c;
}
