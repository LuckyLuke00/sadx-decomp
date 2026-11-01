#include "decls.h"

// GLOBAL: SADX 0x045daa18
static struct CCL_INFO object_c_info[1];

extern struct obj object_big_ita_a_big_ita_a[];

// FUNCTION: SADX 0x00866400
void ObjectBigIta(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	*(struct obj **)((char *)var1 + 8) = object_big_ita_a_big_ita_a;
	ObjectCCollision(tp);
}
