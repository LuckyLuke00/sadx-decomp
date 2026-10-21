#include "decls.h"

// FUNCTION: SADX 0x006a9fc0
void mainBigMR01(int seqno)
{
	switch (seqno)
	{
	case 1:
		SeqChangeStage(0x1a, 3);
		SeqEndSection();
		SeqNext();
		return;
	case 0:
		if (SeqCheckStage(0x21, 2))
		{
			SeqEvent(0xd0);
			SeqNext();
			return;
		}
		break;
	}
}
