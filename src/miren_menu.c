#include "decls.h"

// STUB: SADX 0x008d57e0
signed char MirenMenuGetCommand(struct task *task_p, int *selItem_p, int itemNumb, signed char (*func_p)(struct task *))
{
	return (signed char)0;
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
