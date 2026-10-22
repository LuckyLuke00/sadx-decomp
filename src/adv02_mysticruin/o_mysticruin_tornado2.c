#include "decls.h"

// STUB: SADX 0x006b0a20
void Tornado2Displayer(struct task *tp)
{
}

// FUNCTION: SADX 0x006b0a90
void ObjectMysticRuinTornado2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (*(char *)&DAT_05b9d744 == 2)
	{
		if (var1->mode == 0)
		{
			tp->disp = Tornado2Displayer;
			var1->mode = 1;
		}
		Tornado2Displayer(tp);
	}
}
