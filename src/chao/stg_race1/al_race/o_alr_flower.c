#include "decls.h"

// GLOBAL: SADX 0x009c8adc
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_009c8af4;

// FUNCTION: SADX 0x00717570
void ObjectAlrWhiteFlower(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8af4);
}

// FUNCTION: SADX 0x00717590
void ObjectAlrPurpleFlower(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8af4.action_p);
}
