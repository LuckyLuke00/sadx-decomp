#include "decls.h"

// GLOBAL: SADX 0x0270c2c4
static struct NJS_POINT3 pos_tical;

// FUNCTION: SADX 0x006bd760
void mainSonicPast01(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x22, 2))
		{
			SeqEvent(0x21);
			SeqNext();
			return;
		}
		break;
	case 1:
		SeqSave();
		SeqNext();
		return;
	case 2:
		if (CheckCollisionP(&pos_tical, 20.0f) == 1)
		{
			SeqEvent(0x22);
			SeqNext();
			return;
		}
		break;
	case 3:
		SetEntranceNumber(1);
		SeqChangeStage(0x21, 2);
		SeqEndSection();
		SeqNext();
		return;
	}
}
