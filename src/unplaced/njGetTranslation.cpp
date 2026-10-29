#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067d490
void njGetTranslation(NJS_MATRIX *m, NJS_POINT3 *p)
{
	if (m == 0)
	{
		m = (NJS_MATRIX *)DAT_0629c518;
	}
	p->x = (*m)[12];
	p->y = (*m)[13];
	p->z = (*m)[14];
}
