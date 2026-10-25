#include "decls.h"

// STUB: SADX 0x0087e4e0
void ObjectCasino6SlotEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x0087e960
void ObjectCasino6Slot(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasino6SlotInit(tp);
	}
}
