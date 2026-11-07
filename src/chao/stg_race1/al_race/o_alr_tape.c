#include "decls.h"

// FUNCTION: SADX 0x00491690
void __fastcall FUN_00491690(struct taskwk *param_1)
{
	struct NJS_POINT3 *var1 = (struct NJS_POINT3 *)((char *)param_1 + 0x14);
	struct NJS_POINT3 *var2 = (struct NJS_POINT3 *)((char *)param_1 + 0x20);
	var1->x += var2->x;
	var1->y += var2->y;
	var1->z += var2->z;
	var2->x *= 0.985f;
	var2->z *= 0.985f;
	var2->y *= 0.98f;
	if (var1->y <= 10.0f)
	{
		var2->z = 0.0f;
		var2->y = 0.0f;
		var2->x = 0.0f;
	}
	else
	{
		var2->y -= 0.005f;
	}
}
