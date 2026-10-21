#include "decls.h"

// FUNCTION: SADX 0x006aa3c0
void mainAmyMR01(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x21, 0))
		{
			FUN_004f5550(0x14f);
			FUN_004f5550(0x150);
			FUN_004f5550(0x155);
			SeqSave();
			SeqNext();
			return;
		}
		break;
	case 1:
		if (SeqCheckStage(0x21, 2))
		{
			if (CheckCollisionP(&pos_finalegg, 100.0f) == 1)
			{
				SeqEvent(0x6e);
				SeqNext();
				return;
			}
		}
		break;
	case 2:
		if (SeqCheckFlag(0x151))
		{
			SeqSave();
			SeqNext();
			return;
		}
		break;
	case 3:
		if (SeqCheckNextStage(0xa, 0))
		{
			SeqEndSection();
			SeqNext();
			return;
		}
		break;
	}
}
