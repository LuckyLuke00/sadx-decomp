#include "decls.h"

// FUNCTION: SADX 0x006801d0
void initKnucklesPast01()
{
	SeqSetTime(0);
}

// FUNCTION: SADX 0x006bd610
void mainKnucklesPast01(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x22, 0))
		{
			SeqEvent(0x84);
			SeqNext();
			return;
		}
		break;
	case 1:
		SeqSave();
		SeqNext();
		return;
	case 2:
		if (CheckCollisionP(&tical_pos, 300.0f) == 1)
		{
			SeqEvent(0x85);
			SeqNext();
			return;
		}
		break;
	case 3:
		SetEntranceNumber(1);
		SeqChangeStage(0x1a, 1);
		SeqEndSection();
		SeqNext();
		return;
	}
}
