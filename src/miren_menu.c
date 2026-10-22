#include "decls.h"

// STUB: SADX 0x008d57e0
signed char MirenMenuGetCommand(struct task *task_p, int *selItem_p, int itemNumb, signed char (*func_p)(struct task *))
{
	return (signed char)0;
}

// STUB: SADX 0x008d5820
void initMenu(struct task *task_p, const struct MenuParam *param_p)
{
}

// STUB: SADX 0x008d58d0
void execMenu(struct task *task_p)
{
}

// STUB: SADX 0x008d5a20
void dispMenu(struct task *task_p)
{
}

// FUNCTION: SADX 0x008d5b20
void destMenu(struct task *task_p)
{
	PadReadOn();
	PauseEnable();
}

// STUB: SADX 0x008d5b30
signed char setItemTask(struct task *parent_p)
{
	return (signed char)0;
}
