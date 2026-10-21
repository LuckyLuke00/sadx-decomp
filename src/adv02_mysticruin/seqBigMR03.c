#include "decls.h"

// FUNCTION: SADX 0x006a9e50
void mainBigMR03(int seqno)
{
	switch (seqno)
	{
		case 0:
			FUN_004f5550(0x1cb);
			SeqNext();
			break;
		case 1:
			if (SeqCheckStage(0x21, 2))
			{
				SeqEvent(0xe2);
				SeqNext();
			}
			break;
		case 2:
			SeqEndSection();
			SeqNext();
			break;
	}
}
