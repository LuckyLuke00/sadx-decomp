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
	struct NJS_POINT3 local_20g[2];
	struct NJS_POINT3COL local_30g;
	union NJS_COLOR local_38g[2];

	local_20g[0].x = x1;
	local_20g[0].y = y1;
	local_20g[0].z = z1;
	local_20g[1].x = x2;
	local_20g[1].y = y2;
	local_20g[1].z = z2;
	*((unsigned char *)&local_38g[0] + 3) = 0xff;
	*((unsigned char *)&local_38g[0] + 2) = 0xff;
	*((unsigned char *)&local_38g[0] + 1) = 0xff;
	*((unsigned char *)&local_38g[0] + 0) = 0xff;
	*((unsigned char *)&local_38g[1] + 3) = 0xff;
	*((unsigned char *)&local_38g[1] + 2) = 0x88;
	*((unsigned char *)&local_38g[1] + 1) = 0x88;
	*((unsigned char *)&local_38g[1] + 0) = 0xbb;
	local_30g.p = local_20g;
	local_30g.col = local_38g;
	local_30g.tex = 0;
	local_30g.num = 2;
	___njDrawLine3D(&local_30g, 1, 0);
}
