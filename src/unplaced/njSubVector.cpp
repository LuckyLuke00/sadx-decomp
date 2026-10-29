#include "decls.h"

// FUNCTION: SADX 0x0067e350
void njSubVector(struct NJS_POINT3 *vd, struct NJS_POINT3 *vs)
{
	vd->x = vd->x - vs->x;
	vd->y = vd->y - vs->y;
	vd->z = vd->z - vs->z;
}
