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

// STUB: SADX 0x0044ebd0
void FUN_0044ebd0(const struct SAlgKinderOrthoQuad *quads, int count, unsigned long color)
{
}

// FUNCTION: SADX 0x0044eec0
void AlgKinderOrthoQPolyBegin()
{
	FUN_00422560(7);
	njSetZUpdateMode(1);
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
