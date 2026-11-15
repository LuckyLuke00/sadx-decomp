#include "decls.h"
extern const struct TaskInfo *DAT_0099226c;

// FUNCTION: SADX 0x005a51d0
void Bg_AL_Race(struct task *task_p)
{
	MirenInitTask(task_p, (const struct TaskInfo *)&DAT_0099226c, 0);
}
