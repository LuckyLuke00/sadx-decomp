#include "decls.h"

// FUNCTION: SADX 0x00493570
void FUN_00493570(struct task *param_1, int param_2)
{
	*(unsigned char *)((char *)*(int *)((char *)param_1 + 0x24) + 2) = (unsigned char)param_2;
}
