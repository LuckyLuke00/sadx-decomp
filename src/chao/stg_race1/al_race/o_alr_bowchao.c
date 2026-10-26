#include "decls.h"
int FUN_00717df0();

// GLOBAL: SADX 0x009c8a60
static struct TaskInfo ObjectTaskInfo;

// GLOBAL: SADX 0x009c8a78
static struct ActionParam DAT_009c8a78;

// FUNCTION: SADX 0x00717130
void ObjectAlrBowChao(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8a78);
}
