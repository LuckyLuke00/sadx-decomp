#include "decls.h"

// FUNCTION: SADX 0x007d4f10
void FUN_007d4f10(struct task *param_1, float param_2, void *param_3)
{
	struct taskwk *var1 = param_1->twp;
	var1->pos.y = param_2;
	*(void **)((char *)var1 + 0x14) = param_3;
}
