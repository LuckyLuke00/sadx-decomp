#include "decls.h"
void FUN_0044c7e0(struct task *param_1);
extern int DAT_05b2ca64[1];

// STUB: SADX 0x0044c7e0
void FUN_0044c7e0(struct task *tp)
{
}

// STUB: SADX 0x0044c830
void AlMsgWarnCreate(int winid, float px, float py, float sx, float sy)
{
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
