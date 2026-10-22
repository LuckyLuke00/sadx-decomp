#include "decls.h"

// FUNCTION: SADX 0x00680870
void initMilesSS04()
{
	if (SeqCheckClearAction(4))
	{
		SeqSetTime(2);
		return;
	}
	SeqSetTime(1);
}
