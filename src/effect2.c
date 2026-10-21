#include "decls.h"
long GetPlayerCharacterName(unsigned char pno);
long CheckCollisionP(struct NJS_POINT3 *vp, float d);
void ___njSetConstantMaterial(struct NJS_ARGB *argb);
struct NJS_POINT3;
struct NJS_ARGB;
void ___njDrawLine3D(struct NJS_POINT3COL *, int, unsigned long);

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

// FUNCTION: SADX 0x004cb1f0
void DrawLineV(struct NJS_POINT3 *pos1, struct NJS_POINT3 *pos2)
{
	struct NJS_POINT3 local_20g[2];
	struct NJS_POINT3COL local_30g;
	union NJS_COLOR local_38g[2];

	local_20g[0].x = pos1->x;
	local_20g[0].y = pos1->y;
	local_20g[0].z = pos1->z;
	local_20g[1].x = pos2->x;
	local_20g[1].y = pos2->y;
	local_20g[1].z = pos2->z;
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

// FUNCTION: SADX 0x004cb290
void ModelTurnWhite(struct taskwk *twp, short BkNumber)
{
	struct NJS_ARGB argb;
	short sVar1;

	sVar1 = (short)(1 << (GetPlayerCharacterName(0)));
	if (BkNumber & sVar1)
	{
		if (CheckCollisionP((struct NJS_POINT3 *)((char *)twp + 0x20), 20.0))
		{
			argb.a = 0.0;
			argb.r = 0.5;
			argb.g = 0.5;
			argb.b = 0.5;
			___njSetConstantMaterial(&argb);
		}
		else
		{
			argb.a = 0.0;
			argb.r = 0.0;
			argb.g = 0.0;
			argb.b = 0.0;
			___njSetConstantMaterial(&argb);
		}
	}
	return;
}
