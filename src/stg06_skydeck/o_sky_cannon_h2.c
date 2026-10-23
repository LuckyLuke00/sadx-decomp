#include "decls.h"

// FUNCTION: SADX 0x00840550
void ObjectSkydeck_cannon_h2_End(struct task *tp)
{
	OCMunregister((struct OCMDATA *)tp->twp->timer.ptr);
}

// FUNCTION: SADX 0x00840fc0
void ObjectSkydeck_cannon_h2(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		ObjectSkydeck_cannon_h2_Init(tp);
	}
}
