#include "decls.h"

// FUNCTION: SADX 0x00680e30
void mainSonicSS05(int seqno)
{
	switch (seqno)
	{
	case 0:
		SeqEvent(0x2a);
		SeqNext();
		return;
	case 1:
		SeqSave();
		SeqNext();
		return;
	case 2:
		SeqCheckNextStage(0x21, 0);
		SeqEndSection();
		CreateCreamManager(0);
		SeqNext();
		return;
	}
}
