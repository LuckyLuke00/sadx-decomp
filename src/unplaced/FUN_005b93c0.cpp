#include "decls.h"
extern int DAT_05edc104[10];

// STUB: SADX 0x005b93c0
void FUN_005b93c0(struct task *param_1)
{
}

// FUNCTION: SADX 0x005b9490
void FUN_005b9490(struct task *param_1)
{
	struct taskwk *local_8 = param_1->twp;
	param_1->ptp = 0;
	DAT_05edc104[(int)(signed char)(*(char *)((char *)local_8 + 1))] = 0;
}
