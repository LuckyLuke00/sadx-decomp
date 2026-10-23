#include "decls.h"

// FUNCTION: SADX 0x007d4cd0
void FUN_007d4cd0(struct task *param_1, float param_2)
{
	*(float *)((char *)param_1->twp + 0x30) = param_2;
}
