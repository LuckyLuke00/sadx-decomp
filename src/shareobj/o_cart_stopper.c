#include "decls.h"

// FUNCTION: SADX 0x008dd790
void FUN_008dd790(struct task *param_1)
{
	struct motionwk *local_8;
	local_8 = param_1->mwp;
	MirenObjFreeMobileLandObject(param_1, *(struct obj **)((char *)local_8 + 0x20));
}

// STUB: SADX 0x008dd910
int FUN_008dd910(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x008ddb20
long slideStopper(struct task *task_p)
{
	return (long)0;
}
