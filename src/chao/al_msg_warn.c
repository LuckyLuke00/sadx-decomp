#include "decls.h"
extern char DAT_05b2ca50[];
void FUN_0044c7e0(struct task *param_1);
extern int DAT_05b2ca64[1];

// STUB: SADX 0x0044c7e0
void FUN_0044c7e0(struct task *param_1)
{
}

// FUNCTION: SADX 0x0044c830
void AlMsgWarnCreate(int winid, float px, float py, float sx, float sy)
{
	struct SAlMsgWin *var1 = (struct SAlMsgWin *)((char *)DAT_05b2ca50 + winid * 24);
	if (*(char *)var1 == 0)
	{
		*(float *)((char *)var1 + 4) = px;
		*(char *)var1 = 1;
		*(float *)((char *)var1 + 8) = py;
		*(float *)((char *)var1 + 0xc) = sx;
		*(float *)((char *)var1 + 0x10) = sy;
		*(void **)((char *)var1 + 0x14) = MAlloc(0x30);
		AlMsgWinCreate(*(struct SAlMsgWin **)((char *)var1 + 0x14));
		AlMsgWinSetPos(*(struct SAlMsgWin **)((char *)var1 + 0x14), px + 16.0, py + 16.0, -1.0f);
		AlMsgWinSetSize(*(struct SAlMsgWin **)((char *)var1 + 0x14), sx - 32.0, sy - 40.0);
	}
}

// STUB: SADX 0x0044c900
void AlMsgWarnDelete(int winid)
{
}

// FUNCTION: SADX 0x0044c940
enum EAlMsgWinStatus AlMsgWarnGetStatus(int winid)
{
	return (enum EAlMsgWinStatus)FUN_0044e2f0((int)(*(struct SAlMsgWin **)((char *)DAT_05b2ca64 + winid * 24)));
}

// STUB: SADX 0x0044c960
void AlMsgWarnOpen(int winid)
{
}

// FUNCTION: SADX 0x0044c990
void AlMsgWarnClear(int winid)
{
	AlMsgWinClear(*(struct SAlMsgWin **)((char *)DAT_05b2ca64 + winid * 24));
}

// STUB: SADX 0x0044c9b0
void AlMsgWarnAddLineC(int winid, const char *cstr)
{
}

// FUNCTION: SADX 0x0044c9f0
void AlMsgWarnWaitCont(int winid)
{
	AlMsgWinWaitCont(*(struct SAlMsgWin **)((char *)DAT_05b2ca64 + winid * 24));
}

// FUNCTION: SADX 0x0044ca10
void AlMsgWarnWaitClose(int winid)
{
	AlMsgWinWaitClose(*(struct SAlMsgWin **)((char *)DAT_05b2ca64 + winid * 24));
}

// STUB: SADX 0x0044ca30
void AlMsgWarnInit()
{
}

// STUB: SADX 0x0044ca80
void AlMsgWarnExit()
{
}
