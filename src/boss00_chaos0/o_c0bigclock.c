#include "decls.h"

// FUNCTION: SADX 0x006e5b80
void exitC0BigClock(struct task *tp)
{
	unsigned char bVar1;

	bVar1 = tp->twp->btimer;
	if (bVar1 & 1)
	{
		tp->twp->btimer = bVar1 & 0xfe;
	}
}

// STUB: SADX 0x006e5ba0
void ObjectC0BigClock(struct task *tp)
{
}
