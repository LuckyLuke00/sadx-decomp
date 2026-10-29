#include "decls.h"
void FUN_0042b090(long param_1);

// FUNCTION: SADX 0x00421470
void njDrawTexture(struct NJS_TEXTURE_VTX *polygon, int count, int tex, int flag)
{
	_gjTrans2D(flag);
	_gjRender2DSet();
	njSetTextureG(tex);
	stDrawTexture(polygon, count);
	_gjRender2DReset();
}

// FUNCTION: SADX 0x004214f0
void njDrawTexture3DExEnd(void)
{
	FUN_007d21b0();
}

// FUNCTION: SADX 0x00421550
void njQuadTextureEnd(void)
{
	_gjRender2DReset();
}

// FUNCTION: SADX 0x00421560
void njSetQuadTexture(long texid, unsigned long col)
{
	stSetQuadColor(col);
	FUN_0042b090(texid);
}

// FUNCTION: SADX 0x004216c0
void njDrawLine2D(struct NJS_POINT2COL *p, int n, float pri, unsigned long attr)
{
	float var1;
	int var2;
	struct NJS_POINT2COL local_14;

	var1 = -1.0 / pri;
	local_14.p = p->p;
	local_14.col = p->col;
	local_14.tex = p->tex;
	local_14.num = p->num;
	if (1.0 < var1)
	{
		var1 = 1.0;
	}
	var2 = (int)attr;
	if (var2 >= 0)
	{
		local_14.tex = 0;
	}
	_gjTrans2D((int)attr & 0x40);
	_gjRender2DSet();
	stDrawLine2D(&local_14, var1);
	_gjRender2DReset();
}

// STUB: SADX 0x00421740
void njDrawPolygon2D(struct NJS_POINT2COL *p, int n, float pri, unsigned long attr)
{
}

// FUNCTION: SADX 0x00421ff0
void njDrawLine3D(struct NJS_POINT3COL *p, int n, unsigned long attr)
{
	struct NJS_POINT3COL local_14;

	local_14.p = p->p;
	local_14.col = p->col;
	local_14.tex = p->tex;
	local_14.num = p->num;
	if ((long)attr >= 0)
	{
		local_14.tex = 0;
	}
	if ((attr & 0x40) != 0)
	{
		_gjTrans3D((enum GJ_DEV_BLEND)2);
	}
	else
	{
		_gjTrans3D((enum GJ_DEV_BLEND)0);
	}
	_gjRender3DSet();
	stDrawLine3D(&local_14);
	FUN_007d21b0();
}

// STUB: SADX 0x00422050
void njDrawQuadTexture(struct NJS_QUAD_TEXTURE *q, float z)
{
}

// STUB: SADX 0x004220c0
void njDrawTriangle2D(struct NJS_POINT2COL *p, int n, float pri, unsigned long attr)
{
}
