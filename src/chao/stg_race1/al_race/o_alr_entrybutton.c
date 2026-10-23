#include "decls.h"
extern struct TaskInfo DAT_009c8b90;
extern struct ActionParam DAT_009c8ba8;
struct FrameParam;

// STUB: SADX 0x00717aa0
void initFrame(struct task *task_p, const struct FrameParam *param_p)
{
}

// FUNCTION: SADX 0x00717b10
void execFrame(struct task *task_p)
{
	if (FUN_004c39c0(task_p) == 0)
	{
		MirenObjCheckCollisionP(task_p->twp, task_p->mwp->spd.x);
	}
}

// FUNCTION: SADX 0x00717b40
void destFrame(struct task *task_p)
{
	MirenObjFreeMobileLandObject(task_p, (struct obj *)task_p->mwp->work.ptr);
}

// FUNCTION: SADX 0x00717dd0
void ObjectAlrEntryButton(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_009c8b90, &DAT_009c8ba8);
}
