#include "decls.h"

// GLOBAL: SADX 0x045da9e8
static struct CCL_INFO object_c_info[1];

extern struct obj object_maruta_all_maruta01_maruta01[];

// FUNCTION: SADX 0x008663d0
void ObjectMaruta(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	var1->counter.ptr = object_maruta_all_maruta01_maruta01;
	ObjectCCollision(tp);
}
