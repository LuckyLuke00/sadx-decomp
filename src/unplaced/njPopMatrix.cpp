#include "decls.h"
extern int DAT_0629c518;
extern int DAT_0629c72c;

// FUNCTION: SADX 0x0067d800
void njPopMatrix(Uint32 n)
{
	if (DAT_0629c72c - n != 0)
	{
		DAT_0629c518 += -n << 6;
		DAT_0629c72c -= n;
	}
}
