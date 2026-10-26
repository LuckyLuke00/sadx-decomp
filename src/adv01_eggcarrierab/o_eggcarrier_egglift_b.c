#include "decls.h"
extern unsigned char DAT_05bafb2b;
extern unsigned char DAT_05bafb90;
extern unsigned char DAT_05bafbcf;
extern unsigned char DAT_05bafc0b;
extern unsigned char DAT_05bafc49;
extern unsigned char DAT_05bafc87;
extern unsigned char DAT_05bafcc8;

// STUB: SADX 0x00699870
void LiftDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x00699a90
int chk_active()
{
	if (slEventBossName != -1)
	{
		DAT_05bafb2b = 1;
		return 0;
	}
	switch (GetPlayerNumber())
	{
		case 0:
			return DAT_05bafb90;
		case 2:
			return DAT_05bafbcf;
		case 3:
			return DAT_05bafc0b;
		case 5:
			return DAT_05bafc49;
		case 6:
			return DAT_05bafc87;
		case 7:
			return DAT_05bafcc8;
	}
	return 0;
}
