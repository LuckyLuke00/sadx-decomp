#include "decls.h"

// GLOBAL: SADX 0x0270c244
static struct NJS_POINT3 pos_tical;

// FUNCTION: SADX 0x006bd270
void mainBigPast01(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckStage(0x22, 1))
			{
				SeqEvent(0xdb);
				SeqNext();
				return;
			}
			break;
		case 1:
			SeqSave();
			SeqNext();
			return;
		case 2:
			if (SeqCheckStage(0x22, 1))
			{
				if (CheckCollisionP(&pos_tical, 40.0f) == 1 || DAT_05baf368[0]->pos.z < 285.0f)
				{
					SeqEvent(0xdc);
					SeqNext();
					return;
				}
			}
			break;
		case 3:
			SeqChangeStage(0x20, 1);
			SeqEndSection();
			SeqNext();
			return;
	}
}
