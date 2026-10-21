#include "decls.h"

// FUNCTION: SADX 0x006a9ea0
void initBigMR02()
{
	if (SeqCheckClearAction(8))
	{
		SeqSetTime(2);
		return;
	}
	SeqSetTime(0);
}

// STUB: SADX 0x006a9ed0
void mainBigMR02(int seqno)
{
}
