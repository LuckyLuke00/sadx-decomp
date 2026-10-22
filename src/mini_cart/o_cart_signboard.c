#include "decls.h"
extern struct TaskInfo DAT_00a09e8c;
extern struct ActionParam DAT_00a09ed4;

// STUB: SADX 0x007e5820
void ObjectCartSignboard1(struct task *task_p)
{
}

// STUB: SADX 0x007e5840
void ObjectCartSignboard2(struct task *task_p)
{
}

// STUB: SADX 0x007e5860
void ObjectCartSignboard3(struct task *task_p)
{
}

// STUB: SADX 0x007e5880
void ObjectCartSignboard4(struct task *task_p)
{
}

// FUNCTION: SADX 0x007e58a0
void ObjectCartSignboard5(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09e8c, &DAT_00a09ed4);
}
