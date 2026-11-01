#include "decls.h"
static void Exec(struct task *tp);

// STUB: SADX 0x00872b30
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00872dd0
void ObjectCasinoWatersmoker(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		var1->wtimer = 0;
		tp->exec = Exec;
	}
}
