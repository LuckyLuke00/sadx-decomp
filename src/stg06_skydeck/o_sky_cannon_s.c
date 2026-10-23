#include "decls.h"

// FUNCTION: SADX 0x0084a830
void ObjectSkydeck_cannon_s(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		ObjectSkydeck_cannon_s_Init(tp);
	}
}
