#include "decls.h"

// FUNCTION: SADX 0x0067d080
void njRotateY(NJS_MATRIX *m, Angle ang)
{
	float fVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;
	float fVar6;

	fVar1 = njSin(ang);
	fVar2 = njCos(ang);
	if (m == NULL)
	{
		m = (NJS_MATRIX *)DAT_0629c518;
	}
	fVar3 = (*m)[0];
	fVar4 = (*m)[1];
	fVar5 = (*m)[2];
	fVar6 = (*m)[3];
	(*m)[0] = fVar2 * fVar3 - fVar1 * (*m)[8];
	(*m)[1] = fVar4 * fVar2 - (*m)[9] * fVar1;
	(*m)[2] = fVar5 * fVar2 - (*m)[10] * fVar1;
	(*m)[3] = fVar6 * fVar2 - (*m)[11] * fVar1;
	(*m)[8] = (*m)[8] * fVar2 + fVar1 * fVar3;
	(*m)[9] = (*m)[9] * fVar2 + fVar1 * fVar4;
	(*m)[10] = (*m)[10] * fVar2 + fVar1 * fVar5;
	(*m)[11] = fVar1 * fVar6 + (*m)[11] * fVar2;
}
