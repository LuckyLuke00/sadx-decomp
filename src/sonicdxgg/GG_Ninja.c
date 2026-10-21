#include "decls.h"
extern void *DAT_060ce760;

// FUNCTION: SADX 0x007f2360
void GG_Finalize()
{
	if (DAT_060ce760)
	{
		syFree(DAT_060ce760);
		DAT_060ce760 = 0;
	}
}
