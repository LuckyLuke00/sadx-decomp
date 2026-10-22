#include "decls.h"
extern signed char DAT_05b35db8;

// STUB: SADX 0x004904d0
long AlrToyEntryToy(struct task *task_p, void (*func_p)(struct task *, int), signed char kind)
{
	return (long)0;
}

// STUB: SADX 0x00490550
long GetTargetToyPosition(struct NJS_POINT3 *pos_p, int chaoId)
{
	return (long)0;
}

// STUB: SADX 0x004905c0
void initToy(struct task *task_p, const void *param_p)
{
}

// STUB: SADX 0x004905e0
void execToy(struct task *task_p)
{
}

// FUNCTION: SADX 0x00490650
void destToy(struct task *task_p)
{
	DAT_05b35db8 = 0;
}
