#include "decls.h"
extern struct task *DAT_060cbf64;
static void initChaos0Task(struct task *p_task);

// STUB: SADX 0x007ce8c0
static void initChaos0Task(struct task *p_task)
{
}

// FUNCTION: SADX 0x007ce8e0
void FUN_007ce8e0(float param_1, float param_2, float param_3, long param_4)
{
	struct taskwk *var1;
	char *var2;

	DAT_060cbf64 = CreateElementalTask(2, 5, initChaos0Task);
	var2 = (char *)MAlloc(0x20);
	var1 = DAT_060cbf64->twp;
	var1->pos.x = param_1;
	var1->value.ptr = var2;
	var1->pos.y = param_2;
	var1->mode = 0;
	var1->ang.y = param_4;
	var1->pos.z = param_3;
	var1->scl.x = 0.8f;
	var1->scl.y = 0.8f;
	var1->scl.z = 0.8f;
	var1->counter.f = 0.0f;
	*(unsigned char *)(var2 + 0x1c) = 0x99;
}
