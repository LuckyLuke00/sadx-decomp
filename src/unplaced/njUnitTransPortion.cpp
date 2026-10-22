#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067da10
void njUnitTransPortion(int param_1)
{
	if (param_1 == 0)
	{
		param_1 = DAT_0629c518;
	}
	*(float *)((char *)param_1 + 0x30) = 0.0f;
	*(float *)((char *)param_1 + 0x34) = 0.0f;
	*(float *)((char *)param_1 + 0x38) = 0.0f;
	*(float *)((char *)param_1 + 0x3c) = 1.0f;
}
