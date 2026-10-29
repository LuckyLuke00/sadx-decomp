#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067da10
void njUnitTransPortion(int m)
{
	if (m == 0)
	{
		m = DAT_0629c518;
	}
	*(float *)((char *)m + 0x30) = 0.0f;
	*(float *)((char *)m + 0x34) = 0.0f;
	*(float *)((char *)m + 0x38) = 0.0f;
	*(float *)((char *)m + 0x3c) = 1.0f;
}
