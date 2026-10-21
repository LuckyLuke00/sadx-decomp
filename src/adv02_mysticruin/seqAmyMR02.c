#include "decls.h"

// FUNCTION: SADX 0x006aa330
void initAmyMR02()
{
	if (SeqCheckClearAction(10))
	{
		SeqSetTime(0);
		return;
	}
	SeqSetTime(2);
}

// STUB: SADX 0x006aa360
void mainAmyMR02(int seqno)
{
}
