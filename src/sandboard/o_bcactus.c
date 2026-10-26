#include "decls.h"
extern void *DAT_0353b030;
extern void *DAT_0353afb0;
// GLOBAL: SADX 0x00a0aa60
static struct TaskInfo CactusTaskInfo;
extern void *DAT_0353aff0;

// FUNCTION: SADX 0x007e8380
void ObjectBigCactusA(struct task *task_p)
{
	MirenInitTask(task_p, &CactusTaskInfo, &DAT_0353afb0);
}

// FUNCTION: SADX 0x007e83a0
void ObjectBigCactusB(struct task *task_p)
{
	MirenInitTask(task_p, &CactusTaskInfo, &DAT_0353aff0);
}

// FUNCTION: SADX 0x007e83c0
void ObjectBigCactusC(struct task *task_p)
{
	MirenInitTask(task_p, &CactusTaskInfo, &DAT_0353b030);
}
