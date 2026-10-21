#include "decls.h"
void FUN_004f5550(int param_1);

// FUNCTION: SADX 0x006aa010
void initE102MR04()
{
	if (SeqCheckClearAction(5))
	{
		SeqSetTime(2);
	}
}

// FUNCTION: SADX 0x006aa030
void mainE102MR04(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckClearAction(5))
		{
			SeqEvent(0xc5);
			SeqNext();
			return;
		}
		break;
	case 1:
		FUN_004f5550(0x199);
		SeqClrFlag(0x56);
		SeqNext();
		return;
	case 2:
		SeqCheckNextStage(0x1d, 0);
		SeqEndSection();
		SeqNext();
		return;
	}
}
