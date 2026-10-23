#include "decls.h"

// FUNCTION: SADX 0x00680420
void mainAmySS02(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckStage(0x1a, 3))
			{
				SeqEvent(0x6d);
				SeqNext();
				return;
			}
			break;
		case 1:
			FUN_004f5550(0x146);
			FUN_004f5550(0x147);
			FUN_004f5550(0x14d);
			FUN_004f5550(0x153);
			SeqSave();
			SeqNext();
			return;
		case 2:
			SetEntranceNumber(0);
			SeqChangeStage(0x21, 0);
			SeqEndSection();
			SeqNext();
			return;
	}
}
