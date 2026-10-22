#include "decls.h"

// FUNCTION: SADX 0x006809d0
void mainMilesSS03(int seqno)
{
	switch (seqno)
	{
	case 0:
		SeqEvent(0x56);
		SeqNext();
		return;
	case 1:
		SeqSave();
		SeqNext();
		return;
	case 2:
		SeqCheckNextStage(0x21, 0);
		SeqEndSection();
		CreateCreamManager(1);
		SeqNext();
		return;
	}
}
