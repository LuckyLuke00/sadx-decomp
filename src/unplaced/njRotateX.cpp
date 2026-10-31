#include "decls.h"

// FUNCTION: SADX 0x0067d4c0
void njRotateX(NJS_MATRIX *m, Angle ang)
{
	float local_8;
	float local_10;
	float fVar3;
	float fVar4;
	float fVar5;
	float fVar6;

	local_8 = njSin(ang);
	local_10 = njCos(ang);
	if (m == NULL)
	{
		m = (NJS_MATRIX *)DAT_0629c518;
	}
	fVar3 = (*m)[4];
	fVar4 = (*m)[5];
	fVar5 = (*m)[6];
	fVar6 = (*m)[7];
	(*m)[4] = local_8 * (*m)[8] + local_10 * fVar3;
	(*m)[5] = local_8 * (*m)[9] + fVar4 * local_10;
	(*m)[6] = fVar5 * local_10 + (*m)[10] * local_8;
	(*m)[7] = fVar6 * local_10 + (*m)[11] * local_8;
	(*m)[8] = (*m)[8] * local_10 - local_8 * fVar3;
	(*m)[9] = local_10 * (*m)[9] - local_8 * fVar4;
	(*m)[10] = (*m)[10] * local_10 - local_8 * fVar5;
	(*m)[11] = (*m)[11] * local_10 - local_8 * fVar6;
}
