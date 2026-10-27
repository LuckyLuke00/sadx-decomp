#include "decls.h"

// FUNCTION: SADX 0x00492060
long SendTargetPalmCommand(struct task *objTask_p, struct task *chaoTask_p, signed char cmnd)
{
	struct motionwk *var1;
	long var2;
	var1 = objTask_p->mwp;
	var2 = 0;
	if (*(struct task **)((char *)var1 + 0x18) == chaoTask_p)
	{
		switch (cmnd)
		{
		case 0:
			*(struct task **)((char *)var1 + 0x18) = NULL;
			var2 = 1;
			break;
		case 1:
			if (*(signed char *)((char *)var1 + 0) == 1)
			{
				*(signed char *)((char *)var1 + 0) = 2;
				var2 = 1;
			}
			break;
		case 2:
			if (*(signed char *)((char *)var1 + 0) == 2)
			{
				*(signed char *)((char *)var1 + 0) = 3;
				*(struct task **)((char *)var1 + 0x18) = NULL;
				var2 = 1;
			}
			break;
		}
	}
	return var2;
}
