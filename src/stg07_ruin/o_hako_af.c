#include "decls.h"

// FUNCTION: SADX 0x00854b20
void Exp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->scl.y < -10.0f)
		{
			DeadOut(tp);
			return;
		}
		var1->scl.x += 1.0f;
		var1->scl.y -= 0.2f;
		*(float *)((char *)var1 + 0x24) += var1->scl.y;
		DispExp(tp);
	}
}
