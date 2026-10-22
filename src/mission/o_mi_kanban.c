#include "decls.h"

// FUNCTION: SADX 0x0049c420
void ObjectMiKanban(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		var1->ang.x = 0;
		var1->ang.z = 0;
		var1->mode = 0;
		tp->exec = (void (__cdecl *)(struct task *))0x49c320;
		tp->dest = (void (__cdecl *)(struct task *))0x7d21b0;
		tp->disp = (void (__cdecl *)(struct task *))0x49c290;
	}
}
