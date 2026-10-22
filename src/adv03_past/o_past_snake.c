#include "decls.h"

// FUNCTION: SADX 0x006c1010
void ObjectPastSnake(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->disp = DisplaySnake;
			var1->mode = 1;
		}
		DisplaySnake(tp);
	}
}
