#include "decls.h"

// FUNCTION: SADX 0x00680d30
void mainSonicSS06(int seqno)
{
	switch (seqno)
	{
	case 0:
		SeqEvent(0x11);
		SeqNext();
		return;
	case 1:
		SeqClrFlag(0x82);
		SeqClrFlag(0x88);
		SeqClrFlag(0xa1);
		SeqClrFlag(0x52);
		SeqSave();
		SeqNext();
		return;
	case 2:
		if (SeqCheckStage(0x1a, 1))
		{
			SeqEvent(0x12);
			Playable(5);
			SeqNext();
			return;
		}
		break;
	case 3:
		if (SeqCheckStage(0x1a, 3))
		{
			if (DAT_05baf368[0]->pos.x > 320.0f && DAT_05baf368[0]->pos.z > 1530.0f)
			{
				SeqEvent(0x13);
				FUN_004f5550(0x89);
				SeqNext();
				return;
			}
		}
		break;
	case 4:
		SeqChangeStage(3, 0);
		SeqEndSection();
		SeqNext();
		return;
	}
}
