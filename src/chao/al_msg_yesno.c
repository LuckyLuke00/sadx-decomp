#include "decls.h"
extern char DAT_05b313bc[64];
extern int DAT_05b314b8;
extern struct task *DAT_05b313a0;

// FUNCTION: SADX 0x0044e0e0
void AlMsgSelectSetCStr(int winid, int itemid, const char *cstr)
{
	AlMsgFontColorSet(0, 0xffffffff);
	AlMsgFontCreateCStr((struct SAlMsgFontStr *)(DAT_05b313bc + winid * 0x44 + itemid * 0xc), cstr, DAT_05b3ebbc == 0, 0x270f);
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
