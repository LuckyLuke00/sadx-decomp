#include "decls.h"
extern struct TaskInfo DAT_009c8b90;
extern struct ActionParam DAT_009c8ba8;
struct FrameParam;

// FUNCTION: SADX 0x00717aa0
void initFrame(struct task *task_p, const struct FrameParam *param_p)
{
	const struct obj *var1 = *(const struct obj **)param_p;
	struct obj *var2 = MirenObjAllocMobileLandObject(var1);
	struct motionwk *var3 = task_p->mwp;
	var3->work.ptr = var2;
	if (var2 == 0)
	{
		FreeTask(task_p);
		return;
	}
	MirenObjSetObjectMatrix(var2, task_p->twp, 1.0f);
	MirenObjEntryMobileLandObject(task_p, var2, 1, 1.0f);
	MirenObjClearForceWork(task_p->fwp);
	var3->spd.x = var1->model->r * 2.0f;
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
