#include "decls.h"
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);

// FUNCTION: SADX 0x0067dba0
void njSetMatrix(float *param_1, float *param_2)
{
	if (param_1 == (float *)0x0)
	{
		param_1 = (float *)DAT_0629c518;
	}
	memcpy(param_1, param_2, 0x40);
}
