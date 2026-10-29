#include "decls.h"
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);

// FUNCTION: SADX 0x0067dba0
void njSetMatrix(NJS_MATRIX *md, NJS_MATRIX *ms)
{
	if (md == NULL)
	{
		md = (NJS_MATRIX *)DAT_0629c518;
	}
	memcpy(md, ms, 0x40);
}
