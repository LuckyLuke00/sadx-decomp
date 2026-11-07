#include "decls.h"
extern "C" double fabs(double param_1);

// FUNCTION: SADX 0x0067d8f0
Float njDistanceP2PL(NJS_POINT3 *p, NJS_PLANE *pl, NJS_POINT3 *cp)
{
	float fVar1;
	float fVar2;
	float fVar3;
	float fVar4;

	fVar1 = -(pl->px * pl->vx + pl->py * pl->vy + pl->pz * pl->vz);
	fVar2 = p->x * pl->vx + p->y * pl->vy + p->z * pl->vz + fVar1;
	fVar3 = pl->vx * pl->vx + pl->vy * pl->vy + pl->vz * pl->vz;
	if (cp != NULL)
	{
		fVar4 = -fVar2 / fVar3;
		cp->x = p->x + fVar4 * pl->vx;
		cp->y = p->y + fVar4 * pl->vy;
		cp->z = p->z + fVar4 * pl->vz;
	}
	fVar4 = njSqrt(fVar3);
	fVar3 = 1.0f / fVar4;
	fVar2 = fabs(fVar2);
	fVar4 = fVar3 * fVar2;
	return fVar4;
}
