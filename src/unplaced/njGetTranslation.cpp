#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067d490
void njGetTranslation(int m, float *p)
{
	if (m == 0)
	{
		m = DAT_0629c518;
	}
	*p = *(float *)((char *)m + 0x30);
	p[1] = *(float *)((char *)m + 0x34);
	p[2] = *(float *)((char *)m + 0x38);
}
