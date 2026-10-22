#include "decls.h"

// FUNCTION: SADX 0x006803d0
void mainE102SS01(int seqno)
{
	switch (seqno)
	{
		case 0:
			FUN_004f5550(0x180);
			FUN_004f5550(0x56);
			SeqSave();
			CreateCreamManager(4);
			SeqNext();
			break;
		case 1:
			if (SeqCheckNextStage(1, 0))
			{
				SeqEndSection();
				SeqNext();
			}
			break;
	}
}
