#include "decls.h"
extern int DAT_05b314b8;
extern struct task *DAT_05b313a0;

// FUNCTION: SADX 0x0044e1a0
void AlMsgSelectExit()
{
	if (--DAT_05b314b8 == 0)
	{
		if (DAT_05b313a0)
		{
			FreeTask(DAT_05b313a0);
			DAT_05b313a0 = 0;
		}
	}
}
