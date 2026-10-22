#include "decls.h"
extern unsigned char DAT_05bafb4b;
extern int DAT_05cda154;
void SetChangeGameMode(short mode);
void ChangeStageWithFadeOut(unsigned char stg, unsigned char act);
void SeqNext();
void SeqEndSection();
void SeqEvent(long no);
long SeqCheckStage(long stg, long act);

// FUNCTION: SADX 0x00680640
void mainAmySS00(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x1a, 0) != 0)
		{
			SeqEvent(0x60);
			SeqNext();
		}
		break;
	case 1:
		DAT_05cda154 = (DAT_05bafb4b != 0) - 1 & 4;
		ChangeStageWithFadeOut(0x1a, 0);
		SetChangeGameMode(1);
		SeqEndSection();
		SeqNext();
		break;
	}
}

// FUNCTION: SADX 0x006aae80
void initAmySS00()
{
	SeqSetTime(1);
}
