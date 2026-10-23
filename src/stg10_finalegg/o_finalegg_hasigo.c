#include "decls.h"
void FUN_00893db0(struct task *param_1);

// FUNCTION: SADX 0x00893e40
void Hasigo_Exec(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		FUN_00893db0(tp);
		EntryColliList(tp->twp);
		LoopTaskC(tp);
	}
}
