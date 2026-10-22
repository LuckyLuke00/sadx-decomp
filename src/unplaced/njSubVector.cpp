#include "decls.h"

// FUNCTION: SADX 0x0067e350
void njSubVector(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2)
{
	param_1->x = param_1->x - param_2->x;
	param_1->y = param_1->y - param_2->y;
	param_1->z = param_1->z - param_2->z;
}
