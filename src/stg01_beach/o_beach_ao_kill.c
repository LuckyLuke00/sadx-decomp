#include "decls.h"
void FUN_007f9f90(struct task *param_1);

// FUNCTION: SADX 0x007f9ff0
void ObjectBeachAttackOrukaKill(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = FUN_007f9f90;
}
