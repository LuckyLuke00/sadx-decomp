#include "decls.h"

// FUNCTION: SADX 0x0087e4e0
void ObjectCasino6SlotEnd(struct task *tp)
{
	ObjCasino_EndTexUvInfo((struct TEXUVINFO *)0x0480c798, 3);
}

// FUNCTION: SADX 0x0087e960
void ObjectCasino6Slot(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasino6SlotInit(tp);
	}
}
