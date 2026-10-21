#include "decls.h"
extern int DAT_05b3ea28;

// FUNCTION: SADX 0x006aafb0
void mainSonicMR03(int seqno)
{
	switch (seqno)
	{
	case 0:
		*(char *)((char *)DAT_05b3ea28 + 0x1) = 2;
		SeqSave();
		SeqNext();
		break;
	case 1:
		if (SeqCheckStage(0x21, 0))
		{
			FUN_004f5550(0x9a);
			SeqNext();
		}
		break;
	case 2:
		SeqEvent(0x16);
		SeqNext();
		break;
	case 3:
		if (SeqCheckStage(0x21, 1) && SeqCheckNextStage(5, 0))
		{
			SeqEndSection();
			SeqNext();
		}
		break;
	}
}
