#include "decls.h"
void FUN_007e5960(struct task *param_1);
static void destObject(struct task *task_p);
static void execObject(struct task *task_p);
static void initObject(struct task *task_p, void *param_p);
extern void *DAT_00a09ec8;
extern void *DAT_00a09ebc;
extern void *DAT_00a09eb0;
extern void *DAT_00a09ea4;
extern struct TaskInfo DAT_00a09e8c;
extern struct ActionParam DAT_00a09ed4;

// FUNCTION: SADX 0x007e5820
void ObjectCartSignboard1(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09e8c, &DAT_00a09ea4);
}

// FUNCTION: SADX 0x007e5840
void ObjectCartSignboard2(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09e8c, &DAT_00a09eb0);
}

// FUNCTION: SADX 0x007e5860
void ObjectCartSignboard3(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09e8c, &DAT_00a09ebc);
}

// FUNCTION: SADX 0x007e5880
void ObjectCartSignboard4(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09e8c, &DAT_00a09ec8);
}

// FUNCTION: SADX 0x007e58a0
void ObjectCartSignboard5(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09e8c, &DAT_00a09ed4);
}

#pragma optimize("", off)
// STUB: SADX 0x007e58c0
static void initObject(struct task *task_p, void *param_p)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007e5a20
static void destObject(struct task *task_p)
{
	MirenObjFreeMobileLandObject(task_p, (struct obj *)*(void **)((char *)task_p->mwp + 0x14));
}

#pragma optimize("", off)
// STUB: SADX 0x007e5a40
static void execObject(struct task *task_p)
{
}
#pragma optimize("", on)

// GLOBAL: SADX 0x00a09e8c
struct TaskInfo DAT_00a09e8c = {28, 6, initObject, execObject, FUN_007e5960, destObject};
