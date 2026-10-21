#include "decls.h"
extern struct task *DAT_05cda19c;

// FUNCTION: SADX 0x005a06b0
void FreeAdvaTitleNewTask()
{
	if (DAT_05cda19c)
	{
		DestroyTask(DAT_05cda19c);
	}
}
