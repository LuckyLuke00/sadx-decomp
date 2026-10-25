#include "decls.h"
extern long (*DAT_00961ed8[6])(struct task *, struct task *, signed char);
struct task;

// FUNCTION: SADX 0x00490040
long AlrCommuSendObjCommand(struct task *objTask_p, struct task *chaoTask_p, signed char cmnd, signed char kind)
{
	if (objTask_p == NULL || chaoTask_p == NULL)
		return 0;
	if (DAT_00961ed8[kind] == NULL)
		return 0;
	return DAT_00961ed8[kind](objTask_p, chaoTask_p, cmnd);
}
