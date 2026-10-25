#include "decls.h"
extern unsigned char DAT_05bafb94;
extern unsigned char DAT_05bafbd3;
extern unsigned char DAT_05bafc90;
extern int DAT_060b9104;

// FUNCTION: SADX 0x006b0d60
void WindyValleyDestructor(struct task *tp)
{
	DAT_060b9104 = 0;
}

// FUNCTION: SADX 0x006b0d70
int chk_windyvalley()
{
	switch (GetPlayerNumber())
	{
		case 0:
			if (SeqCheckFlag(0xa7))
				return SeqCheckFlag(0xa8);
			return DAT_05bafb94;
		case 2:
			if (SeqCheckFlag(0xe1))
				return SeqCheckFlag(0xe2);
			return DAT_05bafbd3;
		case 6:
			if (SeqCheckFlag(0x19c))
				return SeqCheckFlag(0x19d);
			return DAT_05bafc90;
	}
	return 0;
}

// STUB: SADX 0x006b1140
void spexec_smoke(struct sp_task *tp, struct sp_link *lp)
{
}

// STUB: SADX 0x006b1360
void FUN_006b1360(void)
{
}

// STUB: SADX 0x006b1d40
void create_leaf(float x, float y, float z, float rad)
{
}
