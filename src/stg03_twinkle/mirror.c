#include "decls.h"

// FUNCTION: SADX 0x00812d00
struct task *createMirrorTask(struct task *tp)
{
	struct task *var1;
	var1 = CreateChildTask(8, execMirrorTask, tp);
	if (var1 != 0)
	{
		var1->awp->work.ul[0] = 0;
		return var1;
	}
	return 0;
}
