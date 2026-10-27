#include "decls.h"
extern int DAT_05b9d838;
extern struct TaskInfo DAT_00a0a940;
extern struct ActionParam DAT_0353aef0;

// FUNCTION: SADX 0x007e7660
void ObjectSandBoardGate(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a0a940, &DAT_0353aef0);
}
