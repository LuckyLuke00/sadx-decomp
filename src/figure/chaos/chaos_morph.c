#include "decls.h"

// STUB: SADX 0x008c7360
struct MORPHWK *morph_water_set(struct obj *object, struct taskwk *twp)
{
	return (struct MORPHWK *)0;
}

// FUNCTION: SADX 0x008c7480
void clrMorphWater(struct MORPHWK *p)
{
	*(char *)p = 6;
	morph_water_act(p);
}
