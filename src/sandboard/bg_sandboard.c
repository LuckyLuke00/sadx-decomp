#include "decls.h"
extern struct TaskInfo DAT_00a0a32c;

// STUB: SADX 0x007e6e00
void initBg(struct task *task_p, const void *param_p)
{
}

// FUNCTION: SADX 0x007e6e40
void Bg_SandBoard(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a0a32c, 0);
}
