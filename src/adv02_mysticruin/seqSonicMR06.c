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

// FUNCTION: SADX 0x006aae40
void mainSonicMR06(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckClearAction(0xa))
			{
				SeqEvent(0x26);
				SeqNext();
			}
			break;
		case 1:
			SeqEndSection();
			SeqNext();
			break;
	}
}
