#include "decls.h"

// STUB: SADX 0x004314b0
Sint8 *njOpenBinary(const char *fname)
{
	return (Sint8 *)0;
}

// FUNCTION: SADX 0x00431550
void njCloseBinary(Sint8 *wbuff)
{
	syFree(wbuff);
}
