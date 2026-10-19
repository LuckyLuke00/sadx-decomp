#include "decls.h"

void njSetPerspective(long param_1);
void njSetConstantMaterial(NJS_ARGB *param_1);

extern long DAT_06298c64;
extern long DAT_05b39e6c;
extern NJS_ARGB DAT_05b39de4;
extern NJS_TEXLIST *DAT_05b3ded0;
extern int DAT_05b39eb4;
extern unsigned char DAT_05b39e10;
extern unsigned char DAT_05b3e065;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x004a0220
void ___njSetPerspective(long a)
{
	if (DAT_06298c64 != a)
	{
		njSetPerspective(a);
	}
	DAT_05b39e6c = a;
	DAT_06298c64 = a;
}

// FUNCTION: SADX 0x004a0250
long ds_GetPerspective()
{
	return DAT_05b39e6c;
}

// FUNCTION: SADX 0x004a0260
void ___njSetBackColor(unsigned long c0, unsigned long c1, unsigned long c2)
{
	c0 |= 0xff000000;
	c1 |= 0xff000000;
	c2 |= 0xff000000;
	njSetBackColor(c0, c1, c2);
}

// FUNCTION: SADX 0x004a02a0
void ___njReleaseTextureAll()
{
	njReleaseTextureAll();
	late_execCancel();
	MSG_CloseRequestCls();
}

// FUNCTION: SADX 0x004a02c0
void ___njSetConstantMaterial(NJS_ARGB *argb)
{
	DAT_05b39de4 = *argb;
	if (DAT_05b39de4.a > 1.0)
	{
		DAT_05b39de4.a = 1.0;
	}
	else if (DAT_05b39de4.a < -1.0)
	{
		DAT_05b39de4.a = -1.0;
	}
	if (DAT_05b39de4.r > 1.0)
	{
		DAT_05b39de4.r = 1.0;
	}
	else if (DAT_05b39de4.r < -1.0)
	{
		DAT_05b39de4.r = -1.0;
	}
	if (DAT_05b39de4.g > 1.0)
	{
		DAT_05b39de4.g = 1.0;
	}
	else if (DAT_05b39de4.g < -1.0)
	{
		DAT_05b39de4.g = -1.0;
	}
	if (DAT_05b39de4.b > 1.0)
	{
		DAT_05b39de4.b = 1.0;
	}
	else if (DAT_05b39de4.b < -1.0)
	{
		DAT_05b39de4.b = -1.0;
	}
	njSetConstantMaterial(&DAT_05b39de4);
}

// FUNCTION: SADX 0x004a03f0
void ___njSetTexture(NJS_TEXLIST *texlist)
{
	long local_8;

	DAT_05b3ded0 = texlist;
	DAT_05b39eb4 = 0;
	local_8 = njSetTexture(texlist);
}

// FUNCTION: SADX 0x004a0420
void ___njSetTextureNum(int num)
{
	DAT_05b39eb4 = num;
	if (DAT_05b3ded0 != 0)
	{
		njSetTextureNum(num);
	}
}

// FUNCTION: SADX 0x004a0450
int ___dsSetTexture()
{
	njSetTexture(DAT_05b3ded0);
	return DAT_05b39eb4;
}

// FUNCTION: SADX 0x004a0470
void ___njColorBlendingMode(int tgt, int mode)
{
	if (tgt == 0)
	{
		DAT_05b39e10 = (DAT_05b39e10 & ~0xf) | (mode & 0xf);
	}
	else if (tgt == 1)
	{
		DAT_05b39e10 = (DAT_05b39e10 & 0xf) | ((mode & 0xf) << 4);
	}
	njColorBlendingMode(tgt, mode);
}

// FUNCTION: SADX 0x004a04d0
void ___njDrawTexture(struct NJS_TEXTURE_VTX *v, int num, int ind, int tf)
{
	int local_8;

	local_8 = DAT_05b3e065;
	if (DAT_05b9d838)
	{
		return;
	}
	if (local_8)
	{
		___njFogDisable();
	}
	njDrawTexture(v, num, ind, tf);
	if (local_8)
	{
		___njFogEnable();
	}
}

// FUNCTION: SADX 0x004a0620
int FUN_004a0620(int param_1)
{
	unsigned int local_ci;
	unsigned int local_8g;
	int local_10;

	local_ci = *(unsigned int *)(*(int *)(param_1 + 0x10) + 0x10);
	local_10 = 0;
	if (local_ci & 0x100000)
	{
		local_10 = 1;
	}
	local_8g = local_ci & 0xfc000000;
	if (local_8g == 0x84000000 || local_8g == 0x24000000 || local_8g == 0x30000000)
	{
		local_10 = ((local_ci & 0x2000000) != 0) + 1;
	}
	return local_10;
}

// FUNCTION: SADX 0x004a0690
void late_ReleaseTexture(NJS_TEXLIST *tl)
{
	int local_8g;
	int local_cj;
	int local_10;

	if (isTextureNG(tl, 0))
	{
		return;
	}
	njReleaseTexture(tl);
}

// FUNCTION: SADX 0x004a0740
int dsCheckView(float x, float y, float z, float radius)
{
	struct NJS_POINT3 ft;
	ft.x = x;
	ft.y = y;
	ft.z = z;
	return dsCheckViewV(&ft, radius);
}
