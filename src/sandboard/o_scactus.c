#include "decls.h"

// FUNCTION: SADX 0x007e7e00
void ObjectSmallCactusA(struct task *task_p)
{
	MirenInitTask(task_p, &CactusTaskInfo, (void *)0x353af30);
}

// FUNCTION: SADX 0x007e7e20
void ObjectSmallCactusB(struct task *task_p)
{
	MirenInitTask(task_p, &CactusTaskInfo, (void *)0x353af70);
}

// STUB: SADX 0x007e80d0
void dispPiece(struct task *task_p)
{
}
