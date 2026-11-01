#include "decls.h"

// GLOBAL: SADX 0x0270c274
static struct NJS_POINT3 pos_tical;

// FUNCTION: SADX 0x006bd4c0
void mainKnucklesPast03(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x22, 2))
		{
			SeqEvent(0x96);
			SeqNext();
			return;
		}
		break;
	case 1:
		SeqSave();
		SeqNext();
		return;
	case 2:
		if (CheckCollisionP(&pos_tical, 30.0f) == 1)
		{
			SeqEvent(0x97);
			SeqNext();
			return;
		}
		break;
	case 3:
		SetEntranceNumber(1);
		SeqChangeStage(0x1d, 5);
		SeqEndSection();
		SeqNext();
		return;
	}
}
