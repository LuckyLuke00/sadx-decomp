#include "decls.h"

// FUNCTION: SADX 0x0069cbf0
void ObjectECCommonDoor(struct task *tp)
{
	tp->twp->flag |= 0x400;
	tp->exec = ObjectECCommonDoorS;
}
