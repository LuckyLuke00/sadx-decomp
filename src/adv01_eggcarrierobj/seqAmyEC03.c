#include "decls.h"

// FUNCTION: SADX 0x006a71d0
void mainAmyEC03(int seqno)
{
	switch (seqno)
	{
	case 0:
		SeqSave();
		SeqNext();
		break;
	case 1:
		if (SeqCheckStage(0x1d, 0))
		{
			SeqEvent(0x71);
			SeqNext();
		}
		break;
	case 2:
		SeqChangeStage(0x17, 0);
		SeqNext();
		break;
	case 3:
		if (SeqCheckClearAction(0x17))
		{
			goto end;
		}
		break;
	case 4:
		SeqEvent(0x72);
		SeqNext();
		break;
	case 5:
		SeqEndSection();
	end:
		SeqNext();
		break;
	}
}
