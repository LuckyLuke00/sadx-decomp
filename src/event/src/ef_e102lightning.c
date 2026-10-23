#include "decls.h"
extern struct task *DAT_060cc958;

// FUNCTION: SADX 0x007d8b60
void ef_e102lightning_loop(struct task *tp)
{
	LoopTaskC(tp);
}

// STUB: SADX 0x007d8ce0
void Create_e102lightning(float x, float y, float z, long childtask_num)
{
}

// FUNCTION: SADX 0x007d8d30
void Delete_e102lightning()
{
	if (DAT_060cc958)
	{
		FreeTask(DAT_060cc958);
		DAT_060cc958 = 0;
	}
}
