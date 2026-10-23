#include "decls.h"
extern unsigned int DAT_060dbc38;
extern struct task *DAT_060dc25c;

// STUB: SADX 0x0086caa0
void ObjectCasinoKinkaiEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x0086cc20
int GetKinkaiNum()
{
	if (DAT_060dc25c != NULL)
	{
		if (DAT_060dbc38 > 0x270f)
		{
			return 0x270f;
		}
		return DAT_060dbc38;
	}
	return 0;
}

// FUNCTION: SADX 0x0086cc40
long SetKinkaiNum(int num)
{
	if (DAT_060dc25c != 0)
	{
		DAT_060dbc38 = (unsigned int)num;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0086d1e0
void ObjectCasinoKinkai(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasinoKinkaiInit(tp);
	}
}
