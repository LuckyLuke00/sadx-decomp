#include "decls.h"
extern int DAT_05cda154;

// FUNCTION: SADX 0x006a9c80
void mainLastMR02(int seqno)
{
	switch (seqno)
	{
	case 0:
		SeqEvent(0xf9);
		SeqNext();
		return;
	case 1:
		if (SeqCheckStage(0x21, 2))
		{
			SeqEvent(0xfa);
			SeqNext();
			return;
		}
		break;
	case 2:
		DAT_05cda154 = 1;
		SeqChangeStage(0x13, 0);
		SeqNext();
		return;
	}
}
