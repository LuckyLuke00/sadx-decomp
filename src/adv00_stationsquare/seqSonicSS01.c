#include "decls.h"

// FUNCTION: SADX 0x00681100
void mainSonicSS01(int seqno)
{
	switch (seqno)
	{
	case 1:
		SeqChangeStage(0xf, 0);
		SeqEndSection();
		SeqNext();
		return;
	case 0:
		if (SeqCheckStage(0x1a, 3))
		{
			SeqEvent(1);
			SeqNext();
			return;
		}
		break;
	}
}

// FUNCTION: SADX 0x006aa880
void initSonicSS01()
{
	SeqSetTime(2);
}
