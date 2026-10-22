#include "decls.h"

// FUNCTION: SADX 0x007075c0
void Rd_E101_R(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode++;
	if (var1->mode >= 2)
	{
		var1->mode = 0;
		tp->exec = BossExec;
	}
}
