#include "decls.h"
extern int DAT_05cda154;

// FUNCTION: SADX 0x006a9e00
void mainLastMR00(int seqno)
{
	switch (seqno)
	{
		case 0:
			SeqEvent(0xf0);
			SeqNext();
			break;
		case 1:
			DAT_05cda154 = 2;
			ChangeStageWithFadeOut(0x21, 2);
			SetChangeGameMode(1);
			SeqEndSection();
			SeqNext();
			break;
	}
}
