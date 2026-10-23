#include "decls.h"
void eggkanban_draw(struct task *task_p);

// STUB: SADX 0x00894080
void eggkanban_draw(struct task *task_p)
{
}

// FUNCTION: SADX 0x00894140
void eggkanban_end(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (var1->value.ptr != 0)
	{
		Free(*(void **)((char *)var1->value.ptr + 0x10));
		Free(var1->value.ptr);
	}
}

// STUB: SADX 0x008941e0
void eggkanban_exec(struct task *task_p)
{
}
