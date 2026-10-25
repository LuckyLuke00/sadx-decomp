#include "decls.h"

// FUNCTION: SADX 0x006aa900
void mainMilesMR05(int seqno)
{
	switch (seqno)
	{
		case 0:
			SeqEvent(0x52);
			SeqNext();
			break;
		case 1:
			SeqEndSection();
			SeqNext();
			break;
	}
}
