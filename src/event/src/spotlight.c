#include "decls.h"
extern struct NJS_TEXLIST texlist_ev_spotlight;
extern struct obj _object_heli_light_light[1];

// STUB: SADX 0x007da1a0
void light_draw(struct task *tp)
{
}

// STUB: SADX 0x007da3a0
void light_init(struct task *tp)
{
}

// FUNCTION: SADX 0x007da440
void light_turn(struct task *tp, float x, float y, float z)
{
	struct taskwk *var1 = tp->twp;
	var1->scl.x = x;
	var1->mode = 1;
	var1->scl.y = y;
	var1->scl.z = z;
}
