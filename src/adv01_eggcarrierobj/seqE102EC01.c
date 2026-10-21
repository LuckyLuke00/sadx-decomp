#include "decls.h"

// FUNCTION: SADX 0x006a7170
void mainE102EC01(int seqno)
{
	switch (seqno)
	{
	case 0:
		SeqSave();
		SeqNext();
		break;
	case 1:
		if (SeqCheckStage(0x20, 1) != 0)
		{
			SeqEvent(0xb7);
			SeqNext();
		}
		break;
	case 2:
		FUN_004f5550(0x180);
		SeqChangeStage(0x1a, 3);
		SeqEndSection();
		SeqNext();
		break;
	}
}
