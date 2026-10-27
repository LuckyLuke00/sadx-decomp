#include "decls.h"

#pragma optimize("", off)
// STUB: SADX 0x008489d0
void ObjectSkydeck_c_connect_Init(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00848ab0
void ObjectSkydeck_c_connect(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_connect_Init(tp);
	}
}
