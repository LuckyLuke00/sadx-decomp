#include "decls.h"
extern int flg_transform[8];
extern unsigned char DAT_05bafb90;
extern unsigned char DAT_05bafbcf;
extern unsigned char DAT_05bafc0b;
extern unsigned char DAT_05bafc49;
extern unsigned char DAT_05bafcc8;

// STUB: SADX 0x00692ca0
void ec_bgmcontrol(struct task *tp)
{
}

// FUNCTION: SADX 0x00692ce0
void colli_passage(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	if (var1->mode == 0)
	{
		if (CheckCollisionCylinderP(&pos_passage, 50.0f, 30.0f) == 1)
		{
			SetEntranceNumber(1);
			SeqChangeStage(0x1d, 3);
			var1->mode = 1;
		}
	}
}

// FUNCTION: SADX 0x00692d30
int lift_active()
{
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

// FUNCTION: SADX 0x00692da0
void FUN_00692da0()
{
	unsigned char *var1 = (unsigned char *)flg_transform[GetPlayerNumber()] + 0x5bafb00;
	*var1 = (*var1 == 0);
}

// FUNCTION: SADX 0x006930f0
void DestroyMapEC(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapEC);
	late_ReleaseTexture(&texlist_mapEC);
}
