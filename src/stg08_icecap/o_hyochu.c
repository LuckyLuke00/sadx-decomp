#include "decls.h"

// GLOBAL: SADX 0x045dadd8
static struct CCL_INFO object_c_info[4];

static void Normal2(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00867e10
static void Normal2(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00867f60
void ObjectHyochu4(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.f = 3.0f;
	CCL_Init(tp, &object_c_info[1], 2, 4);
	var1->mode = 1;
	tp->exec = Normal2;
	tp->disp = Normal2;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
