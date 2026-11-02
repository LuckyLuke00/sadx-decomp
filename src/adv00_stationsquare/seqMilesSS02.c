#include "decls.h"

// FUNCTION: SADX 0x00680a20
void mainMilesSS02(int seqno)
{
	switch (seqno)
	{
	case 0:
		FUN_004f5550(0xc0);
		FUN_004f5550(0xc2);
		FUN_004f5550(0xcb);
		SeqSave();
		SeqNext();
		return;
	case 2:
		if (SeqCheckStage(0x1a, 1) && SeqCheckClearAction(9))
		{
			FUN_004f5550(0xc4);
			SeqEvent(0x177);
			SeqNext();
			return;
		}
		break;
	case 3:
		SeqEvent(0x35);
		SeqNext();
		return;
	case 4:
		ChangeStageWithFadeOut(0x1a, 1);
		SetChangeGameMode(1);
		SeqEndSection();
	case 1:
		SeqNext();
		return;
	}
}
