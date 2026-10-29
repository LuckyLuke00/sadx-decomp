#include "decls.h"

// FUNCTION: SADX 0x0067e460
void njScaleV(NJS_MATRIX *m, NJS_VECTOR *v)
{
	float fVar1;
	float fVar2;
	float fVar3;

	fVar1 = v->x;
	fVar2 = v->y;
	fVar3 = v->z;
	if (m == NULL)
	{
		m = (NJS_MATRIX *)DAT_0629c518;
	}
	(*m)[0] *= fVar1;
	(*m)[1] *= fVar1;
	(*m)[2] *= fVar1;
	(*m)[3] *= fVar1;
	(*m)[4] *= fVar2;
	(*m)[5] *= fVar2;
	(*m)[6] *= fVar2;
	(*m)[7] *= fVar2;
	(*m)[8] *= fVar3;
	(*m)[9] *= fVar3;
	(*m)[10] *= fVar3;
	(*m)[11] *= fVar3;
}
