#include "decls.h"
static void cNormal2(struct task *ctp);
static void Normal2(struct task *tp);

// GLOBAL: SADX 0x0480d6c0
static struct CCL_INFO object_c_info[2];

// STUB: SADX 0x00886e30
static void cNormal2(struct task *ctp)
{
}

// STUB: SADX 0x00886ee0
static void Normal2(struct task *tp)
{
}

// FUNCTION: SADX 0x00886fd0
void ObjectBumper2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2;
	struct taskwk *var3;

	var2 = CreateChildTask(2, cNormal2, tp);
	var3 = var2->twp;
	var3->pos.x = var1->pos.x;
	var3->pos.y = var1->pos.y;
	var3->pos.z = -80.0f;
	CCL_Init(var2, &object_c_info[1], 1, 4);
	var2 = CreateChildTask(2, cNormal2, tp);
	var3 = var2->twp;
	var3->pos.x = var1->pos.x;
	var3->pos.y = var1->pos.y;
	var3->pos.z = -36.5f;
	CCL_Init(var2, &object_c_info[1], 1, 4);
	var1->flag &= 0xfdff;
	tp->exec = Normal2;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
