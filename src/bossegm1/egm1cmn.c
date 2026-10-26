#include "decls.h"
extern "C" double fabs(double param_1);
extern "C" double atan2(double v, double u);
extern "C" double atan2(double v, double u);
extern "C" double atan2(double v, double u);

// STUB: SADX 0x006c2c50
void ZBezier3(struct NJS_POINT3 *ans, struct NJS_POINT3 *pnt3p, float t)
{
}

// FUNCTION: SADX 0x006c2ce0
long ZCalcAngY(struct NJS_POINT3 *vecp)
{
	return (long)(atan2((double)vecp->x, (double)vecp->z) * 65536.0 / 6.283184);
}

// FUNCTION: SADX 0x006c2d00
long ZCalcAbsAngY(struct NJS_POINT3 *vecp)
{
	return (long)(atan2(vecp->x, vecp->z) * 65536.0 / 6.283184) & 0xffff;
}

// FUNCTION: SADX 0x006c2d30
long MissileCalcAngX(struct NJS_POINT3 *vecp)
{
	float var1;
	var1 = fabs(vecp->z);
	return (long)(atan2(vecp->y, var1) * 65536.0 / -6.283184);
}

// STUB: SADX 0x006c2d60
long ZRandomS(long area)
{
	return (long)0;
}

// FUNCTION: SADX 0x006c2da0
unsigned short ZCountMdl(struct obj *obj)
{
	unsigned short local_8 = 1;
	if (obj->child)
	{
		local_8 = ZCountMdl(obj->child) + 1;
	}
	if (obj->sibling)
	{
		local_8 += ZCountMdl(obj->sibling);
	}
	return local_8;
}

// FUNCTION: SADX 0x006c2df0
void ZRotateYXZ(float *matp, struct Angle3 *angp)
{
	if (angp->z != 0)
	{
		njRotateZ(matp, (unsigned short)angp->z);
	}
	if (angp->x != 0)
	{
		njRotateX(matp, (unsigned short)angp->x);
	}
	if (angp->y != 0)
	{
		njRotateY(matp, (unsigned short)angp->y);
	}
}
