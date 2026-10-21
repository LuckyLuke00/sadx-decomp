#include "decls.h"
extern int DAT_05cd14d4;

// STUB: SADX 0x00494750
void calcvsyncsyoriochi()
{
}

// FUNCTION: SADX 0x004947b0
long SummaryExit(void *Param)
{
	npSetZCompareMode(1);
	DAT_05cd14d4 = 1;
	ADX_Close();
	GenocideTask();
	LoopTask();
	FUN_007d21b0((void *)1);
	DAT_05cd14d4 = 0;
	return 0;
}

// STUB: SADX 0x00494950
void SummaryTaskDestructor(struct task *tp)
{
}
