#include "decls.h"

// FUNCTION: SADX 0x007e27d0
void fegg_zangai_dest(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->value.ptr != 0)
	{
		Free(var1->value.ptr);
		var1->value.ptr = 0;
	}
}

// STUB: SADX 0x007e2800
void fegg_zangai_draw(struct task *tp)
{
}

// FUNCTION: SADX 0x007e2b60
void fegg_zangai_cons(struct task *tp)
{
	tp->exec = fegg_zangai_exec;
	tp->disp = fegg_zangai_draw;
	tp->dest = fegg_zangai_dest;
}
