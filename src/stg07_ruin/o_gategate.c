#include "decls.h"

// GLOBAL: SADX 0x043ac960
static struct CCL_INFO object_c_info[1];

static void Normal(struct task *tp);

// STUB: SADX 0x00856150
static void Normal(struct task *tp)
{
}

// FUNCTION: SADX 0x008562b0
void ObjectGategate(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, &object_c_info[0], 1, 4);
	var1->counter.f = *(float *)((char *)var1 + 0x24);
	*(unsigned char *)((char *)var1 + 5) = 0;
	tp->exec = Normal;
	tp->disp = Normal;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
