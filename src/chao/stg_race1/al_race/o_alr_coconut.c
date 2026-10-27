#include "decls.h"
static void initObject(struct task *task_p, const struct ActionParam *param_p);
static void dispObject(struct task *task_p);
static void execObject(struct task *param_1);
extern struct TaskInfo DAT_009c8b18;
extern struct ActionParam DAT_009c8b34;

// FUNCTION: SADX 0x00717790
void ObjectAlrCoconut(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_009c8b18, &DAT_009c8b34);
}

#pragma optimize("", off)
// STUB: SADX 0x007177b0
static void initObject(struct task *task_p, const struct ActionParam *param_p)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00717820
static void dispObject(struct task *param_1)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00717890
static void execObject(struct task *param_1)
{
}
#pragma optimize("", on)

// GLOBAL: SADX 0x009c8b18
struct TaskInfo DAT_009c8b18 = {32, 2, (void (*)(struct task *, void *))initObject, execObject, dispObject, 0};
