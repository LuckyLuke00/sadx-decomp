#include "decls.h"
void FUN_00878e40();
extern int DAT_060dc428;

// FUNCTION: SADX 0x00878e90
void ObjectCasinoSoniczo(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		if (GetPlayerCharacterName(0) == 3)
		{
			ObjectCasinoCrashSoniczo(tp);
			return;
		}
		FUN_00878e40();
		if (FUN_004c39c0(tp) == 0 && DAT_060dc428 == 0)
		{
			DAT_060dc428 = (int)var1;
		}
	}
}
