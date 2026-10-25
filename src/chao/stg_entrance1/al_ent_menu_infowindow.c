#include "decls.h"

// FUNCTION: SADX 0x00473cb0
void PersonalRecordWindowDestructor(struct task *tp)
{
	Free(tp->twp);
	tp->twp = 0;
}
