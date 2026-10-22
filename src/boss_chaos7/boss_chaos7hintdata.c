#include "decls.h"
extern int DAT_060c44d8;
extern int DAT_05b3ebbc;
extern const struct HintMessageString *chaos_message000[5];
long GetCountKilledPlayer();

// FUNCTION: SADX 0x00700f30
void c7CheckTikalMessage(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	var1->timer.l++;
	if (var1->counter.l != 0)
	{
		var1->counter.l--;
		return;
	}
	if (GetCountKilledPlayer() >= 1 && var1->timer.l > 0x3c && DAT_060c44d8 == 0)
	{
		DAT_060c44d8 = 1;
		var1->counter.l = 0x2d0;
		ObjectTikalBoss(chaos_message000[DAT_05b3ebbc], 0x7b0);
	}
}
