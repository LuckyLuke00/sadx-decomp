#include "decls.h"
extern struct NJS_POINT3 DAT_0270c260;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern struct taskwk *DAT_05baf368[8];

// FUNCTION: SADX 0x006bd3d0
void mainAmyPast01(int seqno)
{
	static struct NJS_POINT3 var1;

	switch (seqno)
	{
		case 0:
			if (SeqCheckStage(0x22, 0))
			{
				SeqEvent(0x67);
				SeqNext();
				return;
			}
			break;
		case 1:
			SeqSave();
			SeqNext();
			return;
		case 2:
			if (CheckCollisionP(&DAT_0270c260, 30.0f) == 1 || ((DAT_05b9d724 << 8) | DAT_05b9d744) == 0x2201)
			{
				SeqChangeStage(0x22, 1);
				SeqNext();
				return;
			}
			break;
		case 3:
			if (SeqCheckStage(0x22, 1))
			{
				if (DAT_05baf368[0]->pos.z < 500.0)
				{
					SeqEvent(0x68);
					SeqNext();
					return;
				}
			}
			break;
		case 4:
			SeqChangeStage(0x1d, 5);
			SeqEndSection();
			SeqNext();
			return;
	}
}
