#include "decls.h"
extern struct TEXUVINFO texuvinfo[];

// FUNCTION: SADX 0x00873340
void ObjectCasino6Slot2End(struct task *tp)
{
	ObjCasino_EndTexUvInfo(&texuvinfo[0], 3);
}

// FUNCTION: SADX 0x008737c0
void ObjectCasino6Slot2(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasino6Slot2Init(tp);
	}
}
