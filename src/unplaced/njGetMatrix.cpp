#include "decls.h"
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);

// FUNCTION: SADX 0x0067d3f0
void njGetMatrix(float *param_1)
{
	memcpy(param_1, (float *)DAT_0629c518, 0x40);
}
