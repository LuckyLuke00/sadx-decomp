#include "decls.h"
extern struct task *DAT_060b85a8[10];
extern struct NJS_POINT2 DAT_05b3e050;
extern short DAT_05b9d744;
extern struct NJS_ARGB **pFogTable_Adv01C[2];
extern struct NJS_POINT2 **pClipSky_Adv01C[2];
extern struct NJS_POINT2 **pClipMap_Adv01C[2];
extern struct NJS_POINT3 **pScale_Adv01C[2];

// FUNCTION: SADX 0x0069da90
void BgActInit(struct task *tp)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Adv01C + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Adv01C + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Adv01C + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Adv01C + local_8))[DAT_05b3e0d0];
}

// FUNCTION: SADX 0x0069db40
void FUN_0069db40(void)
{
	int var1;

	for (var1 = 0; var1 < 8; var1++)
	{
		if (DAT_060b85a8[var1] != 0)
		{
			DestroyTask(DAT_060b85a8[var1]);
			DAT_060b85a8[var1] = 0;
		}
	}
}

// STUB: SADX 0x0069dbe0
void FUN_0069dbe0(struct task *param_1)
{
}

// FUNCTION: SADX 0x0069dc30
long LoadMapECH(unsigned short act)
{
	if (act > 5)
		return 0;
	texLoadTexturePvmFile("map_ec_h", &texlist_mapECH);
	FUN_004b6460(&texlist_mapECH, "map_ec_h");
	return 1;
}

// FUNCTION: SADX 0x0069ddd0
void DestroyMapECH(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapECH);
	late_ReleaseTexture(&texlist_mapECH);
}

// STUB: SADX 0x0069dec0
void Bg_EggCarrierC(struct task *tp)
{
}
