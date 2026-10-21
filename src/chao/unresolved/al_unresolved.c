#include "decls.h"
extern int DAT_05b360c0;
extern int DAT_05b360bc;
extern int DAT_023469fc;

// FUNCTION: SADX 0x00494170
void chCnkSetOffsetAlpha(float alpha)
{
	if (DAT_023469fc)
		___OutputDebugString("chCnkSetOffsetAlpha\n");
}

// FUNCTION: SADX 0x004941d0
void chCnkDrawObject(struct cnkobj *pObject)
{
	___beforecnk();
	njCnkDrawObject(pObject);
	___aftercnk();
}

// FUNCTION: SADX 0x004941f0
void chCnkDrawMotion(const struct cnkobj *object, const struct NJS_MOTION *motion, float frame)
{
	___beforecnk();
	njCnkDrawMotion(object, motion, frame);
	___aftercnk();
}

// FUNCTION: SADX 0x00494220
void saCnkDrawMotionSA(const struct cnkobj *object, const struct NJS_MOTION *motion, float frame)
{
	___beforecnk();
	njCnkSetShortAngleUser();
	njCnkDrawMotion(object, motion, frame);
	njCnkClrShortAngleUser();
	___aftercnk();
}

// FUNCTION: SADX 0x00494250
void saCnkDrawMotionLinkSA(const struct cnkobj *object, const struct NJS_MOTION_LINK *motion_link, float rate)
{
	njCnkSetShortAngleUser();
	___beforecnk();
	njCnkDrawMotionLink(object, motion_link, rate);
	___aftercnk();
	njCnkClrShortAngleUser();
}

// FUNCTION: SADX 0x00494650
enum EGbaStatus GbaStatus(int a)
{
	if (DAT_05b360bc != 0)
	{
		___OutputDebugString("GbaStatus\n");
	}
	return (enum EGbaStatus)2;
}

// FUNCTION: SADX 0x00494670
enum EGbaCheck GbaCheck(int a)
{
	if (DAT_05b360c0)
	{
		___OutputDebugString("GbaCheck\n");
	}
	return (enum EGbaCheck)0;
}

// STUB: SADX 0x00494690
void chCalcWorldPosFromScreenPos(struct NJS_POINT3 *pScreenPos, struct NJS_POINT3 *pWorldPos)
{
}
