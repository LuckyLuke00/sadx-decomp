#include "decls.h"

// FUNCTION: SADX 0x0048a970
struct task *CreateChao_for_ALR_ALRE(void (*func)(struct task *), struct al_status *status)
{
	struct task *var1;
	var1 = CreateElementalTask(2, 3, func);
	if (var1 != NULL && AL_GetALifewk(var1, status) == 0)
	{
		FreeTask(var1);
		return NULL;
	}
	return var1;
}
