#include "decls.h"

// FUNCTION: SADX 0x00448100
void ALO_ObakeHeadDestructor(struct task *tp)
{
	ALW_CancelEntry(tp);
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}
