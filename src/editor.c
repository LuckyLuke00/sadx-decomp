#include "decls.h"
extern short DAT_05ccde90;
extern short DAT_05ccde94;

// FUNCTION: SADX 0x0056e3b0
unsigned long CheckEditMode()
{
	int local_8;
	local_8 = DAT_05ccde90 | DAT_05ccde94;
	return (unsigned long)local_8;
}
