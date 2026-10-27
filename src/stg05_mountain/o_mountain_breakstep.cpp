#include "decls.h"

// FUNCTION: SADX 0x008310d0
void DesertAChildTask(struct task *tp)
{
	Free(tp->twp->value.ptr);
}
