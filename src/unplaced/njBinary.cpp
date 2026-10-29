#include "decls.h"

// STUB: SADX 0x004314b0
void *njOpenBinary(void *fname)
{
	return (void *)0;
}

// FUNCTION: SADX 0x00431550
void njCloseBinary(void *wbuff)
{
	syFree(wbuff);
}
