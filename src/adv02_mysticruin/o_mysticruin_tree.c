#include "decls.h"

// FUNCTION: SADX 0x006b2d20
void ObjectMysticRuinTree(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->disp = TreeDisplayer;
			var1->mode = 1;
		}
		TreeDisplayer(tp);
	}
}
