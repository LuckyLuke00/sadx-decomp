#include "decls.h"

// FUNCTION: SADX 0x008ddd00
void ERSetColli(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	ERSC_CorrectParameter(local_8);
	ERSC_CommonExec(tp);
	tp->exec = ERSC_CommonExec;
}

#pragma optimize("", off)
// STUB: SADX 0x008ddd40
void ERSC_CorrectParameter(struct taskwk *twp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x008de700
void ERSC_DisplayEditInfo(struct task *tp)
{
}
