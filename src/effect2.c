#include "decls.h"
long GetPlayerCharacterName(unsigned char pno);
long CheckCollisionP(struct NJS_POINT3 *vp, float d);
void ___njSetConstantMaterial(struct NJS_ARGB *argb);
struct NJS_POINT3;
struct NJS_ARGB;

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

// STUB: SADX 0x004cb160
void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
}

// FUNCTION: SADX 0x004cb1f0
void DrawLineV(struct NJS_POINT3 *pos1, struct NJS_POINT3 *pos2)
{
	struct NJS_POINT3COL p;
	struct NJS_POINT3 local_20h[2];
	union NJS_COLOR local_38g[2];
	local_20h[0].x = pos1->x;
	local_20h[0].y = pos1->y;
	local_20h[0].z = pos1->z;
	local_20h[1].x = pos2->x;
	local_20h[1].y = pos2->y;
	local_20h[1].z = pos2->z;
	local_38g[0].argb.a = 0xff;
	local_38g[0].argb.r = 0xff;
	local_38g[0].argb.g = 0xff;
	local_38g[0].argb.b = 0xff;
	local_38g[1].argb.a = 0xff;
	local_38g[1].argb.r = 0x88;
	local_38g[1].argb.g = 0x88;
	local_38g[1].argb.b = 0xbb;
	p.p = local_20h;
	p.col = local_38g;
	p.tex = 0;
	p.num = 2;
	___njDrawLine3D(&p, 1, 0);
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
