#include "decls.h"

// FUNCTION: SADX 0x0044ea90
void AlgKinderOrthoBegin()
{
	njPolygonCullingMode(0);
	FUN_00422560(7);
	njSetZUpdateMode(1);
}

// FUNCTION: SADX 0x0044eab0
void AlgKinderOrthoEnd()
{
	FUN_00422560(1);
	njSetZUpdateMode(1);
}

// FUNCTION: SADX 0x0044ebd0
void FUN_0044ebd0(const struct SAlgKinderOrthoQuad *param_1, int param_2, unsigned long param_3)
{
	int var1;

	if (param_2 > 0) {
		var1 = param_2;
		do {
			AlgKinderOrthoQuadDraw(param_1, param_3);
			param_1 = (const struct SAlgKinderOrthoQuad *)((char *)param_1 + 0x10);
			var1--;
		} while (var1 != 0);
	}
}

// STUB: SADX 0x0044ec00
void AlgKinderOrthoQuadDrawArrayOffset(const struct SAlgKinderOrthoQuad *q, int len, unsigned long color, int ox, int oy)
{
}

// FUNCTION: SADX 0x0044eec0
void AlgKinderOrthoQPolyBegin()
{
	FUN_00422560(7);
	njSetZUpdateMode(1);
}

// STUB: SADX 0x0044eee0
void AlgKinderOrthoQPolyDrawZ(float x0, float x1, float y0, float y1, float z, unsigned long color)
{
}

// STUB: SADX 0x0044ef80
void AlgKinderOrthoTriDrawZ(float x0, float y0, float x1, float y1, float x2, float y2, float z, unsigned long color)
{
}

// FUNCTION: SADX 0x0044f030
void AlgKinderOrthoNjTranslate(float x, float y, float z)
{
	struct NJS_POINT3 local_20;
	struct NJS_POINT3 local_14;

	local_20.x = x;
	local_20.y = y;
	local_20.z = z;
	chCalcWorldPosFromScreenPos(&local_20, &local_14);
	njTranslateV(0, &local_14);
}
