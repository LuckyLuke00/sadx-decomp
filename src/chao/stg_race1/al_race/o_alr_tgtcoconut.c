#include "decls.h"
extern NJS_POINT3 DAT_05b35c58[8];

// FUNCTION: SADX 0x00490140
long GetTargetCoconutPosition(struct NJS_POINT3 *pos_p, int chaoId)
{
	if (pos_p && (unsigned int)chaoId <= 7)
	{
		*pos_p = DAT_05b35c58[chaoId];
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00490310
void destObject(struct task *task_p)
{
	AlrCommuSendChaoCommand((struct task *)*(int **)((char *)task_p->mwp + 0x18), task_p, 0, 1);
}
