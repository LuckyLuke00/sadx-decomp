#include "decls.h"

// FUNCTION: SADX 0x00680c60
void initSonicSS07()
{
	if (SeqCheckClearAction(3))
	{
		SeqSetTime(2);
		return;
	}
	SeqSetTime(1);
}

// FUNCTION: SADX 0x00680c90
void mainSonicSS07(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckClearAction(3))
			{
				FUN_004f5550(0x8a);
				SeqEvent(0x14);
				SeqNext();
				return;
			}
			break;
		case 1:
			if (SeqCheckStage(0x1a, 3))
			{
				FUN_004f5550(0x8b);
				SeqEvent(0x179);
				SeqNext();
				return;
			}
			break;
		case 2:
			SeqSave();
			SeqNext();
			return;
		case 3:
			if (SeqCheckNextStage(4, 0))
			{
				SeqEndSection();
				SeqNext();
				return;
			}
			break;
	}
}
