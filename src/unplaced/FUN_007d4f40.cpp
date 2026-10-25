#include "decls.h"

// FUNCTION: SADX 0x007d4f40
void FUN_007d4f40(struct task *param_1, int param_2)
{
	*(int *)((char *)param_1->twp + 0x1c) = param_2;
}
