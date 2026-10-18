#include "decls.h"

extern struct NJS_ARGB DAT_05b9d7dc;
extern struct NJS_ARGB DAT_05b9d7ec;

// FUNCTION: SADX 0x004cb0e0
void SetMaterial(float a, float r, float g, float b)
{
	DAT_05b9d7dc.a = a;
	DAT_05b9d7dc.r = r;
	DAT_05b9d7dc.g = g;
	DAT_05b9d7dc.b = b;
	___njSetConstantMaterial(&DAT_05b9d7dc);
}

// FUNCTION: SADX 0x004cb120
void SetMatMatMaterial()
{
	___njSetConstantMaterial(&DAT_05b9d7dc);
}

// FUNCTION: SADX 0x004cb140
void ResetMaterial()
{
	___njSetConstantMaterial(&DAT_05b9d7ec);
}

// FUNCTION: SADX 0x004cb160
void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
	struct NJS_POINT3 a1[2];
	struct NJS_POINT3COL f1;
	union NJS_COLOR cl[2];

	a1[0].x = x1;
	a1[0].y = y1;
	a1[0].z = z1;
	a1[1].x = x2;
	a1[1].y = y2;
	a1[1].z = z2;
	*((unsigned char *)&cl[0] + 3) = 0xff;
	*((unsigned char *)&cl[0] + 2) = 0xff;
	*((unsigned char *)&cl[0] + 1) = 0xff;
	*((unsigned char *)&cl[0] + 0) = 0xff;
	*((unsigned char *)&cl[1] + 3) = 0xff;
	*((unsigned char *)&cl[1] + 2) = 0x88;
	*((unsigned char *)&cl[1] + 1) = 0x88;
	*((unsigned char *)&cl[1] + 0) = 0xbb;
	f1.p = a1;
	f1.col = cl;
	f1.tex = 0;
	f1.num = 2;
	___njDrawLine3D(&f1, 1, 0);
}
