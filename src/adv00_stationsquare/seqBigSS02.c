#include "decls.h"

// FUNCTION: SADX 0x006801e0
void mainBigSS02(int seqno)
{
	switch (seqno)
	{
	case 0:
		FUN_004f5550(0x1c0);
		FUN_004f5550(0x1c6);
		SeqSave();
		SeqNext();
		return;
	case 1:
		if (SeqCheckStage(0x1a, 3))
		{
			SeqEvent(0xe3);
			SeqNext();
			return;
		}
		break;
	case 2:
		if (SeqCheckNextStage(1, 2))
		{
			SeqEndSection();
			SeqNext();
			return;
		}
		break;
	}
}
