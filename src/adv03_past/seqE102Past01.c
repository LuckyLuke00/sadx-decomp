#include "decls.h"

// FUNCTION: SADX 0x006bd330
void mainE102Past01(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckStage(0x22, 1))
			{
				SeqEvent(0xb9);
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
				if (DAT_05baf368[0]->pos.z < 800.0)
				{
					SeqEvent(0xba);
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
