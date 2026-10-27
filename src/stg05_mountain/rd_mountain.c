#include "decls.h"
extern struct obj object_soto_ec_kazecolijon_ec_kazecolijon[1];
extern struct NJS_ARGB *pFogTable_Stg05[];
extern struct NJS_POINT2 *pClipSky_Stg05[];
extern struct NJS_POINT2 *pClipMap_Stg05[];
extern struct NJS_POINT3 *pScale_Stg05[];

// FUNCTION: SADX 0x00827ac0
void SetTableBg_mountain(int c_level)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Stg05 + local_8))[c_level];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Stg05 + local_8))[c_level];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Stg05 + local_8))[c_level];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Stg05 + local_8))[c_level];
}

// STUB: SADX 0x00827b70
void mt_gdcontrol(struct task *tp)
{
}

// FUNCTION: SADX 0x00827e80
void Object_Mountain_KN_Display(struct task *tp)
{
	tp->twp->timer.ptr = object_soto_ec_kazecolijon_ec_kazecolijon;
}

// STUB: SADX 0x008284e0
void Object_Mountain_Knuckles(struct task *tp)
{
}
