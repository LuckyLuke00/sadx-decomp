#include "decls.h"

// FUNCTION: SADX 0x00680c60
void initSonicSS07()
{
	if (SeqCheckClearAction(3))
	{
		SeqSetTime(2);
		return;
	}
	SeqSetTime(1);
}
