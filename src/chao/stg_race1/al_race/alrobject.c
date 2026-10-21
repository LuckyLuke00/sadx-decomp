#include "decls.h"
extern struct task *DAT_05b35c50;

// FUNCTION: SADX 0x0048a7f0
void AlrObjFreeManageTask()
{
	if (DAT_05b35c50)
	{
		FreeTask(DAT_05b35c50);
		DAT_05b35c50 = 0;
	}
}
