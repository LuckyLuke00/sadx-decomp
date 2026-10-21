#include "decls.h"
void FUN_004f5550(int param_1);

// FUNCTION: SADX 0x006aae90
void mainSonicMR05(int seqno)
{
	switch (seqno)
	{
		case 0:
			FUN_004f5550(0x9d);
			SeqNext();
			return;
		case 1:
			if (SeqCheckStage(0x21, 2))
			{
				SeqEvent(0x23);
				SeqNext();
				return;
			}
			break;
		case 2:
			SeqSave();
			SeqNext();
			return;
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
