#include "decls.h"

// FUNCTION: SADX 0x006bd170
void mainLastPast01(int seqno)
{
	switch (seqno)
	{
	case 0:
		SeqEvent(0xf6);
		SeqNext();
		return;
	case 1:
		if (*(float *)((char *)DAT_05baf368 + 0x28) < 500.0)
		{
			SeqEvent(0xf7);
			SeqNext();
			return;
		}
		break;
	case 2:
		SeqEvent(0x160);
		SeqNext();
		return;
	case 3:
		if (CheckCollisionP(&pos_tical, 50.0f) == 1)
		{
			SeqEvent(0xfb);
			SeqNext();
			return;
		}
		break;
	case 4:
		if (*(float *)((char *)DAT_05baf368 + 0x24) >= 90.0f && *(float *)((char *)DAT_05baf368 + 0x28) <= 100.0)
		{
			SeqEvent(0xf8);
			SeqNext();
			return;
		}
		break;
	case 5:
		SeqChangeStage(0x21, 1);
		SeqEndSection();
		SeqNext();
		return;
	}
}
