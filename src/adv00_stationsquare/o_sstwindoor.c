#include "decls.h"

// STUB: SADX 0x0068fa50
void FUN_0068fa50(struct task *tp)
{
}

// FUNCTION: SADX 0x0068fbd0
void ObjectWait(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	FUN_0068fa50(tp);
	if (!var1->btimer)
	{
		if (CheckCollisionP(&var1->pos, 15.0f))
		{
			return;
		}
		tp->exec = ObjectClose;
		dsPlay_oneshot(0x212, 0, 0, 0);
	}
	else
	{
		var1->btimer--;
	}
}
