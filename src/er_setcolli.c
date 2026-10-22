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
