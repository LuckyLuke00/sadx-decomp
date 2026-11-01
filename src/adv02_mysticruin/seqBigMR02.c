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

// FUNCTION: SADX 0x006a9ed0
void mainBigMR02(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckStage(0x21, 0))
			{
				FUN_004f5550(0x1cc);
				FUN_004f5550(0x1cf);
				SeqSave();
				SeqEvent(0x17a);
				SeqNext();
				return;
			}
			break;
		case 2:
			if (SeqCheckClearAction(8))
			{
				SeqClrFlag(0x1d2);
				SeqClrFlag(0x57);
				SeqNext();
				return;
			}
			break;
		case 3:
			if (SeqCheckStage(0x21, 0))
			{
				SeqEvent(0xd3);
				SeqNext();
				return;
			}
			break;
		case 4:
			FUN_004f5550(0x1d2);
			FUN_004f5550(0x57);
			SeqNext();
			return;
		case 5:
			SeqCheckNextStage(0x1a, 1);
			SeqEndSection();
		case 1:
			SeqNext();
			return;
	}
}
