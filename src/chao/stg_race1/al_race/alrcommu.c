#include "decls.h"
struct Alr;
extern long (*DAT_00961ed8[6])(struct task *, struct task *, signed char);
struct task;

// STUB: SADX 0x0048ffc0
struct task *AlrCommuGetColliTask(const struct colliwk *colliWk_p)
{
	return (struct task *)0;
}

// STUB: SADX 0x0048fff0
long AlrCommuSendChaoCommand(struct task *chaoTask_p, struct task *objTask_p, signed char cmnd, signed char objKind)
{
	return (long)0;
}

// FUNCTION: SADX 0x00490040
long AlrCommuSendObjCommand(struct task *objTask_p, struct task *chaoTask_p, signed char cmnd, signed char kind)
{
	if (objTask_p == NULL || chaoTask_p == NULL)
		return 0;
	if (DAT_00961ed8[kind] == NULL)
		return 0;
	return DAT_00961ed8[kind](objTask_p, chaoTask_p, cmnd);
}
