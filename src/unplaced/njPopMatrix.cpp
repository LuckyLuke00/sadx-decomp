#include "decls.h"
extern int DAT_0629c518;
extern int DAT_0629c72c;

// FUNCTION: SADX 0x0067d800
void njPopMatrix(int param_1)
{
	if (DAT_0629c72c - param_1 != 0)
	{
		DAT_0629c518 += -param_1 << 6;
		DAT_0629c72c -= param_1;
	}
}
