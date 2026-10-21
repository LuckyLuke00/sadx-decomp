#include "decls.h"
extern struct task *DAT_060cc958;

// FUNCTION: SADX 0x007d8d30
void Delete_e102lightning()
{
	if (DAT_060cc958)
	{
		FreeTask(DAT_060cc958);
		DAT_060cc958 = 0;
	}
}
