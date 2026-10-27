#include "decls.h"
void AL_MaruKageDraw(struct NJS_POINT3 *pPos, struct Angle3 *pAng, float scl, float scl_ratio, float alpha);
extern struct obj DAT_05a862dc;

// STUB: SADX 0x0045a740
void AL_EntryShadowTex(struct NJS_POINT3 *pos, float scl)
{
}

// FUNCTION: SADX 0x0045a790
void AL_MaruKageDraw(struct NJS_POINT3 *pPos, struct Angle3 *pAng, float scl, float scl_ratio, float alpha)
{
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	SetMaterial(alpha, 1.0f, 1.0f, 1.0f);
	SetRegularTexture();
	njPushMatrixEx();
	njTranslateEx(pPos);
	if (pAng->z != 0)
	{
		njRotateZ(0, (unsigned short)pAng->z);
	}
	if (pAng->x != 0)
	{
		njRotateX(0, (unsigned short)pAng->x);
	}
	if (pAng->y != 0)
	{
		njRotateY(0, (unsigned short)pAng->y);
	}
	FUN_0067d2d0(0, scl, 1.0f, scl * scl_ratio);
	___dsDrawObject(&DAT_05a862dc);
	njPopMatrixEx();
	ResetMaterial();
}

// STUB: SADX 0x0045a860
void AL_ShadowDrawDX(struct task *tp, float scl, float scl_ratio, float alpha)
{
}
