#include "decls.h"
static void Normal1(struct task *tp);

// GLOBAL: SADX 0x045dadd8
static struct CCL_INFO object_c_info[4];

static void Normal2(struct task *tp);

// STUB: SADX 0x00867dd0
static void Normal1(struct task *tp)
{
}

// STUB: SADX 0x00867e10
static void Normal2(struct task *tp)
{
}

// FUNCTION: SADX 0x00867ea0
void ObjectHyochu1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, &object_c_info[0], 1, 4);
	var1->mode = 0;
	tp->exec = Normal1;
	tp->disp = Normal1;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00867ee0
void ObjectHyochu2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.f = 3.0f;
	CCL_Init(tp, &object_c_info[0], 1, 4);
	var1->mode = 0;
	tp->exec = Normal2;
	tp->disp = Normal2;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00867f20
void ObjectHyochu3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, &object_c_info[1], 2, 4);
	var1->mode = 1;
	tp->exec = Normal1;
	tp->disp = Normal1;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

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

// FUNCTION: SADX 0x00867fa0
void ObjectHyochu5(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, &object_c_info[3], 1, 4);
	var1->mode = 2;
	tp->exec = Normal1;
	tp->disp = Normal1;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00867fe0
void ObjectHyochu6(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.f = 3.0f;
	CCL_Init(tp, &object_c_info[3], 1, 4);
	var1->mode = 2;
	tp->exec = Normal2;
	tp->disp = Normal2;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
