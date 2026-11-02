#include "decls.h"

// GLOBAL: SADX 0x03e716e8
static struct CCL_INFO object_c_info[3];

static void Normal(struct task *tp);

// STUB: SADX 0x0081e850
static void Normal(struct task *tp)
{
}

// FUNCTION: SADX 0x0081e9d0
void ObjectTokei(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, (struct CCL_INFO *)object_c_info, 3, 4);
	var1->wtimer = 0;
	var1->flag &= 0xfeff;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
	tp->exec = Normal;
	tp->disp = Normal;
}
