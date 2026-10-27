#include "decls.h"

// FUNCTION: SADX 0x006806a0
void mainKnucklesSS02(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x1a, 1))
		{
			SeqEvent(0x86);
			SeqNext();
			return;
		}
		break;
	case 1:
		SeqSave();
		CreateCreamManager(2);
		SeqNext();
		return;
	case 2:
		if (SeqCheckStage(0x1a, 4))
		{
			SeqEvent(0xa0);
			FUN_004f5550(0x12c);
			SeqNext();
			return;
		}
		break;
	case 3:
		if (SeqCheckClearAction(0x10))
			goto end;
		break;
	case 4:
		FUN_004f5550(0x108);
		FUN_004f5550(0x109);
		FUN_004f5550(0x11b);
		SeqChangeStage(0x21, 0);
		SeqEndSection();
	end:
		SeqNext();
		return;
	}
}
