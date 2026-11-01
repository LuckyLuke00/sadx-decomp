#include "decls.h"

// GLOBAL: SADX 0x0480d784
static struct CCL_INFO object_c_info[1];

static void Normal(struct task *tp);

// STUB: SADX 0x00887da0
static void Normal(struct task *tp)
{
}

// FUNCTION: SADX 0x00887e70
void ObjectStartShot(struct task *tp)
{
	CCL_Init(tp, (struct CCL_INFO *)&object_c_info, 1, 4);
	tp->twp->btimer = 0x3c;
	tp->exec = Normal;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
