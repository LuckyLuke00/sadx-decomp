#include "decls.h"

// STUB: SADX 0x0084c560
void EffHodaiBombReflectPlayer(struct taskwk *twp)
{
}

// STUB: SADX 0x0084c5b0
int CountObjElements(struct obj *pobject)
{
	return (int)0;
}

// STUB: SADX 0x0084cdd0
void TaskEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x0084ce50
void TaskInit(struct task *tp)
{
	tp->exec = TaskExec;
	tp->disp = TaskDisp;
	tp->dest = TaskEnd;
}
