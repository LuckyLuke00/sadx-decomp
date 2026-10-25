#include "decls.h"
extern int DAT_05b3ea28;
extern unsigned char DAT_05bafb4a;
extern int DAT_05cda154;
void SetEntranceNumber(signed char number);
void SeqNext();
void SeqEndSection();
long SeqCheckStage(long stg, long act);
void SeqChangeStage(long stg, long act);
void EV_Load2(int no);
void EV_Exec2();

// FUNCTION: SADX 0x006aa890
void mainKnucklesMR01(int seqno)
{
	switch (seqno)
	{
	case 0:
		if (SeqCheckStage(0x21, 1))
		{
			EV_Load2(0x80);
			EV_Exec2();
			SeqNext();
			return;
		}
		break;
	case 1:
		*(char *)((char *)DAT_05b3ea28 + 1) = 2;
		DAT_05cda154 = (DAT_05bafb4a != 0) - 1 & 2;
		SetEntranceNumber(0);
		SeqChangeStage(0x1a, 3);
		SeqEndSection();
		SeqNext();
		return;
	}
}
