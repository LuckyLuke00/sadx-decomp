#include "decls.h"
extern int DAT_05b3ea28;

// FUNCTION: SADX 0x006aa090
void initE102MR03()
{
	if (SeqCheckClearAction(2))
	{
		SeqSetTime(1);
	}
}

// FUNCTION: SADX 0x006aa0b0
void mainE102MR03(int seqno)
{
	switch (seqno)
	{
		case 0:
			if (SeqCheckClearAction(2))
			{
				if (SeqCheckStage(0x21, 0))
				{
					*(char *)((char *)DAT_05b3ea28 + 0x1) = 2;
					FUN_004f5550(0x192);
					FUN_004f5550(0x194);
					SeqEvent(0x17c);
					SeqNext();
					return;
				}
			}
			break;
		case 1:
			if (SeqCheckNextStage(5, 1))
			{
				SeqEndSection();
				SeqNext();
				return;
			}
			break;
	}
}
