#include "decls.h"
extern unsigned long DAT_05cced10;
extern float DAT_05cced18[64];

// FUNCTION: SADX 0x00571750
long GetMMMatrix(unsigned long srcnmb, float *ansmat)
{
	if (srcnmb >= DAT_05cced10)
	{
		return 0;
	}
	njSetMatrix((NJS_MATRIX *)ansmat, (NJS_MATRIX *)((char *)DAT_05cced18 + srcnmb * 0x40));
	return 1;
}
