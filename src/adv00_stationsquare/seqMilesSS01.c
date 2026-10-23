#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x00680ae0
void mainMilesSS01(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (((DAT_05b9d724 << 8) | DAT_05b9d744) == 0x1a03)
		{
			SeqEvent(0x30);
			SeqNext();
			return;
		}
		break;
	case 1:
		SeqChangeStage(1, 1);
		FUN_004f5550(0xc1);
		FUN_004f5550(0xca);
		FUN_004f5550(0xdc);
		FUN_004f5550(0x53);
		SeqNext();
		return;
	case 2:
		if (SeqCheckClearAction(1) && SeqCheckStage(0x1a, 4))
		{
			SeqEvent(0x32);
			SeqNext();
			return;
		}
		break;
	case 3:
		SeqCheckNextStage(0x21, 0);
		SeqEndSection();
		SeqNext();
		return;
	}
}
