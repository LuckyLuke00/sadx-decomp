#include "decls.h"

// FUNCTION: SADX 0x006aaf10
void mainSonicMR04(int seqno)
{
	switch (seqno)
	{
	case 0:
		FUN_004f5550(0x93);
		FUN_004f5550(0x9b);
		FUN_004f5550(0x9c);
		FUN_004f5550(0xa3);
		SeqNext();
		break;
	case 1:
		if (SeqCheckStage(0x21, 2))
		{
			SeqEvent(0x1e);
			SeqNext();
		}
		break;
	case 2:
		Playable(7);
		SeqNext();
		break;
	case 3:
		SeqCheckNextStage(7, 0);
		SeqEndSection();
		SeqNext();
		break;
	}
}
