#include "decls.h"
extern struct TaskInfo DAT_00a0a32c;

// FUNCTION: SADX 0x007e6e40
void Bg_SandBoard(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a0a32c, 0);
}
