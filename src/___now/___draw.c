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
void ___njSetPerspective(long param_1)
{
	if (DAT_06298c64 != param_1)
	{
		njSetPerspective(param_1);
	}
	DAT_05b39e6c = param_1;
	DAT_06298c64 = param_1;
}

// FUNCTION: SADX 0x004a0250
long ds_GetPerspective()
{
	return DAT_05b39e6c;
}

// FUNCTION: SADX 0x004a0260
void ___njSetBackColor(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
	param_1 |= 0xff000000;
	param_2 |= 0xff000000;
	param_3 |= 0xff000000;
	njSetBackColor(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x004a02a0
void ___njReleaseTextureAll()
{
	njReleaseTextureAll();
	late_execCancel();
	MSG_CloseRequestCls();
}

// FUNCTION: SADX 0x004a02c0
void ___njSetConstantMaterial(NJS_ARGB *param_1)
{
	DAT_05b39de4 = *param_1;
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
void ___njSetTexture(NJS_TEXLIST *param_1)
{
	long result;

	DAT_05b3ded0 = param_1;
	DAT_05b39eb4 = 0;
	result = njSetTexture(param_1);
}

// FUNCTION: SADX 0x004a0420
void ___njSetTextureNum(int param_1)
{
	DAT_05b39eb4 = param_1;
	if (DAT_05b3ded0 != 0)
	{
		njSetTextureNum(param_1);
	}
}

// FUNCTION: SADX 0x004a0450
int ___dsSetTexture()
{
	njSetTexture(DAT_05b3ded0);
	return DAT_05b39eb4;
}

// FUNCTION: SADX 0x004a0470
void ___njColorBlendingMode(int param_1, int param_2)
{
	if (param_1 == 0)
	{
		DAT_05b39e10 = (DAT_05b39e10 & ~0xf) | (param_2 & 0xf);
	}
	else if (param_1 == 1)
	{
		DAT_05b39e10 = (DAT_05b39e10 & 0xf) | ((param_2 & 0xf) << 4);
	}
	njColorBlendingMode(param_1, param_2);
}

// FUNCTION: SADX 0x004a04d0
void ___njDrawTexture(struct NJS_TEXTURE_VTX *param_1, int param_2, int param_3, int param_4)
{
	int fog;

	fog = DAT_05b3e065;
	if (DAT_05b9d838)
	{
		return;
	}
	if (fog)
	{
		___njFogDisable();
	}
	njDrawTexture(param_1, param_2, param_3, param_4);
	if (fog)
	{
		___njFogEnable();
	}
}

// FUNCTION: SADX 0x004a0620
int FUN_004a0620(int param_1)
{
	unsigned int flags;
	unsigned int kind;
	int result;

	flags = *(unsigned int *)(*(int *)(param_1 + 0x10) + 0x10);
	result = 0;
	if (flags & 0x100000)
	{
		result = 1;
	}
	kind = flags & 0xfc000000;
	if (kind == 0x84000000 || kind == 0x24000000 || kind == 0x30000000)
	{
		result = ((flags & 0x2000000) != 0) + 1;
	}
	return result;
}

// FUNCTION: SADX 0x004a0690
void late_ReleaseTexture(NJS_TEXLIST *param_1)
{
	int a;
	int b;
	int c;

	if (isTextureNG(param_1, 0))
	{
		return;
	}
	njReleaseTexture(param_1);
}

// FUNCTION: SADX 0x004a0740
int dsCheckView(float x, float y, float z, float r)
{
	struct NJS_POINT3 p;
	p.x = x;
	p.y = y;
	p.z = z;
	return dsCheckViewV(&p, r);
}
