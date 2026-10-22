#include "decls.h"

// FUNCTION: SADX 0x0045d990
long AL_CheckNade(struct task *tp)
{
	long var1;

	var1 = AL_GetBehavior(tp);
	if (var1 != (long)ALBHV_Nade && var1 != (long)ALBHV_Tron && var1 != (long)ALBHV_Cry && var1 != (long)ALBHV_Tameiki && var1 != (long)ALBHV_MesoMeso)
	{
		if (tp->twp->flag & 1)
		{
			if (AL_IsHitKindWithNum(tp, 1, 2))
			{
				AL_SetBehavior(tp, ALBHV_Nade);
				return 1;
			}
		}
	}
	return 0;
}
