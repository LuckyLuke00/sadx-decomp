#include "decls.h"

// GLOBAL: SADX 0x043ac990
static struct CCL_INFO object_c_info[1];

extern struct obj object_lostobj_togetoge_togetoge[];

// FUNCTION: SADX 0x008562f0
void ObjectTogehari(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	var1->counter.ptr = object_lostobj_togetoge_togetoge;
	ObjectCCollision(tp);
}
