#include "decls.h"

// FUNCTION: SADX 0x007d1ff0
void FUN_007d1ff0(struct task *param_1)
{
	param_1->exec = execModelTask;
	param_1->disp = dispModelTask;
	param_1->dest = FUN_007d6940;
}
