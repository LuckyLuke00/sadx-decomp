#include "decls.h"

// FUNCTION: SADX 0x006aae10
void initSonicMR06()
{
	if (SeqCheckClearAction(0xa))
	{
		SeqSetTime(0);
		return;
	}
	SeqSetTime(1);
}

// STUB: SADX 0x006aae40
void mainSonicMR06(int seqno)
{
}
