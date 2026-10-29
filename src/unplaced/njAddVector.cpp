#include "decls.h"

// FUNCTION: SADX 0x0067d8c0
void njAddVector(struct NJS_POINT3 *vd, struct NJS_POINT3 *vs)
{
	vd->x = vd->x + vs->x;
	vd->y = vd->y + vs->y;
	vd->z = vd->z + vs->z;
}
