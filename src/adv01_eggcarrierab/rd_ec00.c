#include "decls.h"
extern int flg_transform[8];
extern unsigned char DAT_05bafb00[];
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
	int var1 = flg_transform[GetPlayerNumber()];
	DAT_05bafb00[var1] = (DAT_05bafb00[var1] == 0);
}

// FUNCTION: SADX 0x00693060
long LoadMapEC(unsigned short act)
{
	switch (act)
	{
	case 0:
		texLoadTexturePvmFile("map_ec_b", &texlist_mapEC);
		break;
	case 1:
	case 2:
		texLoadTexturePvmFile("map_ec_a", &texlist_mapEC);
		break;
	case 3:
	case 4:
	case 5:
		if (SeqCheckFlag(flg_transform[GetPlayerNumber()]))
			texLoadTexturePvmFile("map_ec_a", &texlist_mapEC);
		else
			texLoadTexturePvmFile("map_ec_b", &texlist_mapEC);
		break;
	default:
		return 0;
	}
	FUN_004b6460(&texlist_mapEC, "mapEC");
	return 1;
}

// FUNCTION: SADX 0x006930f0
void DestroyMapEC(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapEC);
	late_ReleaseTexture(&texlist_mapEC);
}

// STUB: SADX 0x00693110
int FUN_00693110(float *param_1)
{
	return (int)0;
}
