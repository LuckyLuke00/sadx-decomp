#include "decls.h"
extern struct ActionParam DAT_00a0aa18;
extern struct ActionParam DAT_00a0a9bc;
extern struct TaskInfo PillarTaskInfo;
extern struct ActionParam DAT_00a0a9ac;
static void destObject(struct task *task_p);
static void dispObject(struct task *task_p);
static void execObject(struct task *task_p);
static void initObject(struct task *task_p, void *param_p);

// FUNCTION: SADX 0x007e78a0
void ObjectPillarS(struct task *task_p)
{
	MirenInitTask(task_p, &PillarTaskInfo, &DAT_00a0a9ac);
}

// FUNCTION: SADX 0x007e78c0
void ObjectPillarM(struct task *task_p)
{
	MirenInitTask(task_p, &PillarTaskInfo, &DAT_00a0a9bc);
}

// FUNCTION: SADX 0x007e78e0
void ObjectPillarL(struct task *task_p)
{
	MirenInitTask(task_p, &PillarTaskInfo, &DAT_00a0aa18);
}

// STUB: SADX 0x007e7900
static void dispObject(struct task *task_p)
{
}

// FUNCTION: SADX 0x007e7960
static void destObject(struct task *task_p)
{
	MirenObjFreeMobileLandObject(task_p, (struct obj *)(*(int *)((char *)task_p->mwp + 0x20)));
}

// STUB: SADX 0x007e7a10
static void initObject(struct task *task_p, void *param_p)
{
}

// STUB: SADX 0x007e7b00
static void execObject(struct task *task_p)
{
}

// GLOBAL: SADX 0x00a0a97c
static struct TaskInfo PillarTaskInfo = {48, 6, initObject, execObject, dispObject, destObject};
