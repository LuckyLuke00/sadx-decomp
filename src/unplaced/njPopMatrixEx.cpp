#include "decls.h"
extern int DAT_0629c518;
extern int DAT_0629c72c;

// FUNCTION: SADX 0x00430990
void njPopMatrixEx(void)
{
	if (DAT_0629c72c > 0)
	{
		DAT_0629c518 -= 0x40;
		DAT_0629c72c--;
	}
}
