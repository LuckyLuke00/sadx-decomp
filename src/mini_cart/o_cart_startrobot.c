#include "decls.h"
extern struct TaskInfo DAT_00a09f08;

// FUNCTION: SADX 0x007e6020
void ObjectCartStartRobot(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09f08, 0);
}
