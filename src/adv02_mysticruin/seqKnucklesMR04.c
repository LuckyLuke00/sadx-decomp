#include "decls.h"
extern unsigned char DAT_05bafb4a;
extern int DAT_05cda154;

// FUNCTION: SADX 0x006aa4e0
void mainKnucklesMR04(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x21, 1))
		{
			SeqEvent(0x9d);
			SeqNext();
			return;
		}
		break;
	case 1:
		DAT_05cda154 = (DAT_05bafb4a != 0) - 1 & 3;
		ChangeStageWithFadeOut(0x21, 1);
		SetChangeGameMode(1);
		SeqEndSection();
		SeqNext();
		return;
	}
}
