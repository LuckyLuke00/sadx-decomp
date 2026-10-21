#include "decls.h"

// FUNCTION: SADX 0x00851f20
void ObjectRuinUkidai(struct task *tp)
{
	tp->twp->timer.ptr = object_ukidai_ukidai_ukidai;
	ObjectGCollision(tp);
}
