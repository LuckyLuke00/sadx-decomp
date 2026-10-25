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

// STUB: SADX 0x004cb160
void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
}

// STUB: SADX 0x004cb1f0
void DrawLineV(struct NJS_POINT3 *pos1, struct NJS_POINT3 *pos2)
{
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
