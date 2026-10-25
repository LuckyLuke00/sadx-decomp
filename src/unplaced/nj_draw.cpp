#include "decls.h"
void njDrawLine2D(struct NJS_POINT2COL *param_1, int param_2, float param_3, unsigned long param_4);
void FUN_0042b090(long param_1);

// FUNCTION: SADX 0x00421470
void njDrawTexture(struct NJS_TEXTURE_VTX *param_1, int param_2, int param_3, int param_4)
{
	_gjTrans2D(param_4);
	_gjRender2DSet();
	njSetTextureG(param_3);
	stDrawTexture(param_1, param_2);
	_gjRender2DReset();
}

// STUB: SADX 0x004214f0
void njDrawTexture3DExEnd(void)
{
}

// FUNCTION: SADX 0x00421550
void njQuadTextureEnd(void)
{
	_gjRender2DReset();
}

// FUNCTION: SADX 0x00421560
void njSetQuadTexture(long param_1, unsigned long param_2)
{
	stSetQuadColor(param_2);
	FUN_0042b090(param_1);
}

// FUNCTION: SADX 0x004216c0
void njDrawLine2D(struct NJS_POINT2COL *param_1, int param_2, float param_3, unsigned long param_4)
{
	float var1;
	int var2;
	struct NJS_POINT2COL local_14;

	var1 = -1.0 / param_3;
	local_14.p = param_1->p;
	local_14.col = param_1->col;
	local_14.tex = param_1->tex;
	local_14.num = param_1->num;
	if (1.0 < var1)
	{
		var1 = 1.0;
	}
	var2 = (int)param_4;
	if (var2 >= 0)
	{
		local_14.tex = 0;
	}
	_gjTrans2D((int)param_4 & 0x40);
	_gjRender2DSet();
	stDrawLine2D(&local_14, var1);
	_gjRender2DReset();
}

// STUB: SADX 0x00421740
void njDrawPolygon2D(struct NJS_POINT2COL *param_1, int param_2, float param_3, unsigned long param_4)
{
}

// STUB: SADX 0x00421ff0
void njDrawLine3D(struct NJS_POINT3COL *param_1, int param_2, unsigned long param_3)
{
}

// STUB: SADX 0x00422050
void njDrawQuadTexture(struct NJS_QUAD_TEXTURE *param_1, float param_2)
{
}

// STUB: SADX 0x004220c0
void njDrawTriangle2D(struct NJS_POINT2COL *param_1, int param_2, float param_3, unsigned long param_4)
{
}
