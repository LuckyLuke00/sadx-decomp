#include "decls.h"

// STUB: SADX 0x008dd390
void ObjectCartStopper(struct task *task_p)
{
}

// FUNCTION: SADX 0x008dd790
void FUN_008dd790(struct task *param_1)
{
	struct motionwk *local_8;
	local_8 = param_1->mwp;
	MirenObjFreeMobileLandObject(param_1, *(struct obj **)((char *)local_8 + 0x20));
}

// STUB: SADX 0x008dd7c0
void getObjectPos(float *pos_t, const struct taskwk *taskWk_p, const struct NJS_ACTION *action_p, float frame)
{
}

// STUB: SADX 0x008dd890
void FUN_008dd890(struct task *param_1, NJS_POINT3 *param_2, NJS_POINT3 *param_3)
{
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
