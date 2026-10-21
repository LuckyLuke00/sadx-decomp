#include "decls.h"
extern struct NJS_POINT3 DAT_026f1b20;

// FUNCTION: SADX 0x006aa930
void mainMilesMR04(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x21, 0))
		{
			SeqEvent(0x46);
			SeqNext();
			return;
		}
		break;
	case 1:
		Playable(7);
		FUN_004f5550(0xd8);
		SeqClrFlag(0xdc);
		SeqClrFlag(0x53);
		SeqNext();
		return;
	case 2:
		if (SeqCheckStage(0x21, 0))
		{
			if (CheckCollisionP(&DAT_026f1b20, 80.0f) == 1)
			{
				SeqEvent(0x47);
				SeqNext();
				return;
			}
		}
		break;
	case 3:
		FUN_004f5550(0xdc);
		FUN_004f5550(0x53);
		SeqChangeStage(5, 1);
		SeqEndSection();
		SeqNext();
		return;
	}
}
