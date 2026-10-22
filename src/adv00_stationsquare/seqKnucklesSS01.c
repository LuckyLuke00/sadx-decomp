#include "decls.h"

// FUNCTION: SADX 0x00680770
void initKnucklesSS01()
{
	if (SeqCheckClearAction(4))
	{
		SeqSetTime(2);
		return;
	}
	SeqSetTime(0);
}
