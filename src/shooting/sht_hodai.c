#include "decls.h"
extern struct taskwk *DAT_05b42a7c;

// FUNCTION: SADX 0x007f0e60
long CheckRangeInSht(struct task *pTask, float fRange)
{
	float local_c = pTask->twp->pos.x - DAT_05b42a7c->pos.x;
	float var1 = pTask->twp->pos.y - DAT_05b42a7c->pos.y;
	float local_8 = pTask->twp->pos.z - DAT_05b42a7c->pos.z;
	if (local_c * local_c + var1 * var1 + local_8 * local_8 > fRange)
	{
		return 0;
	}
	return 1;
}
