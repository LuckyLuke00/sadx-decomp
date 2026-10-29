#include "decls.h"
extern int DAT_0629c518;

// FUNCTION: SADX 0x0067d350
void njTranslateV(float *m, struct NJS_POINT3 *v)
{
	float fVar1;
	float fVar2;
	float fVar3;

	fVar1 = v->x;
	fVar2 = v->y;
	fVar3 = v->z;
	if (m == NULL)
	{
		m = (float *)DAT_0629c518;
	}
	m[12] += fVar1 * m[0] + fVar2 * m[4] + fVar3 * m[8];
	m[13] += fVar1 * m[1] + fVar2 * m[5] + fVar3 * m[9];
	m[14] += fVar1 * m[2] + fVar2 * m[6] + fVar3 * m[10];
	m[15] += fVar1 * m[3] + fVar2 * m[7] + fVar3 * m[11];
}
