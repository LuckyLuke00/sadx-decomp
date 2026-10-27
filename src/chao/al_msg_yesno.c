#include "decls.h"
extern int DAT_05b314b8;
extern struct task *DAT_05b313a0;

// STUB: SADX 0x0044df80
void FExec(struct task *tp)
{
}

// STUB: SADX 0x0044e0e0
void AlMsgSelectSetCStr(int winid, int itemid, const char *cstr)
{
}

// STUB: SADX 0x0044e170
void AlMsgSelectInit()
{
}

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
