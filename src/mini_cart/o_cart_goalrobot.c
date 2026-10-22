#include "decls.h"
extern struct TaskInfo DAT_00a09ee8;

// FUNCTION: SADX 0x007e5d00
void ObjectCartGoalRobot(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a09ee8, 0);
}
