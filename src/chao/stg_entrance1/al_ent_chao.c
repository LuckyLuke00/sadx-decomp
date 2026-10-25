#include "decls.h"

// FUNCTION: SADX 0x00472b50
long ALBHV_Oshaburiburi(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	short *var2 = (short *)((char *)var1 + 0x1c6);
	if (*var2 == 0)
	{
		AL_SetMotionLink(tp, 1);
		(*var2)++;
	}
	return 0;
}
