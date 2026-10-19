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
	float local_10hk;
	float local_44;
	float local_2cz;
	float local_28q;
	float local_1cg;
	float local_3cg;
	unsigned char local_5kt;
	unsigned char local_15g;
	unsigned char local_21i;
	unsigned char local_7gw;
	unsigned char local_35u;
	unsigned char local_2dz;
	unsigned char local_3dh;
	unsigned char local_6;
	float *local_14k;
	unsigned char *local_34hg;
	int local_20k;
	int local_cgt;

	local_10hk = pos1->x;
	local_44 = pos1->y;
	local_2cz = pos1->z;
	local_28q = pos2->x;
	local_1cg = pos2->y;
	local_3cg = pos2->z;
	local_5kt = 0xff;
	local_15g = 0xff;
	local_21i = 0xff;
	local_7gw = 0xff;
	local_35u = 0xff;
	local_2dz = 0x88;
	local_3dh = 0x88;
	local_6 = 0xbb;
	local_14k = &local_10hk;
	local_34hg = &local_5kt;
	local_20k = 0;
	local_cgt = 2;
	___njDrawLine3D((struct NJS_POINT3COL *)&local_14k, 1, 0);
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
