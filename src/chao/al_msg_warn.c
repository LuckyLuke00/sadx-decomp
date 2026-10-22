#include "decls.h"
extern int DAT_05b2ca64[1];

// STUB: SADX 0x0044c900
void AlMsgWarnDelete(int winid)
{
}

// STUB: SADX 0x0044c940
enum EAlMsgWinStatus AlMsgWarnGetStatus(int winid)
{
	return (enum EAlMsgWinStatus)0;
}

// STUB: SADX 0x0044c960
void AlMsgWarnOpen(int winid)
{
}

// STUB: SADX 0x0044c990
void AlMsgWarnClear(int winid)
{
}

// STUB: SADX 0x0044c9b0
void AlMsgWarnAddLineC(int winid, const char *cstr)
{
}

// STUB: SADX 0x0044c9f0
void AlMsgWarnWaitCont(int winid)
{
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
