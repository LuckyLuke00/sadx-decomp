#include "decls.h"

// FUNCTION: SADX 0x00454540
void ALO_ShabonDestructor(struct task *tp)
{
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}
