#include "decls.h"

// STUB: SADX 0x005bd920
void RoboDestructor(struct task *tp)
{
}

// STUB: SADX 0x005bdc30
void FUN_005bdc30(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bde30
void FUN_005bde30(struct task *pTask, struct OBJ_CONDITION *ocp, void *param_3)
{
}

// STUB: SADX 0x005be930
long RoboHearSound(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// FUNCTION: SADX 0x005bf0d0
void FUN_005bf0d0(void *param_1, void *param_2)
{
	*(int *)((char *)param_2 + 0x1c0) = AdjustAngle(*(int *)((char *)param_2 + 0x1c0), *(int *)((char *)param_2 + 0x1d0), *(int *)((char *)param_2 + 0x1c4));
	*(int *)((char *)param_1 + 0x18) = AdjustAngle(*(int *)((char *)param_1 + 0x18), *(int *)((char *)param_2 + 0x1c0), *(int *)((char *)param_2 + 0x1b8));
}

// STUB: SADX 0x005bfdf0
void RoboCombo(struct taskwk *twp, struct enemywk *ewp)
{
}
