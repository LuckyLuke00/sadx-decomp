#include "decls.h"

// FUNCTION: SADX 0x00680bb0
void initSonicSS08()
{
	if (SeqCheckClearAction(4))
	{
		SeqSetTime(0);
		return;
	}
	SeqSetTime(2);
}

// FUNCTION: SADX 0x00680be0
void mainSonicSS08(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckClearAction(4))
			{
				if (SeqCheckStage(0x1a, 1))
				{
					SeqEvent(0x15);
					FUN_004f5550(0xa1);
					FUN_004f5550(0x52);
					FUN_004f5550(0x82);
					FUN_004f5550(0x88);
					SeqNext();
					return;
				}
			}
			break;
		case 1:
			if (SeqCheckNextStage(0x21, 0))
			{
				SeqEndSection();
				SeqNext();
				return;
			}
			break;
	}
}
