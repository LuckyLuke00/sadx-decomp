#include "decls.h"

// FUNCTION: SADX 0x0068b400
void ObjectSSSyoukaki(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, (struct CCL_INFO *)0x26ddf8c, 1, 4);
		tp->exec = (void (*)(struct task *))0x68b3c0;
		tp->disp = (void (*)(struct task *))0x68b350;
	}
}
