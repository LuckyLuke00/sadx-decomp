#include "decls.h"
extern struct NJS_POINT3 *DAT_05b32e50;
extern "C" int rand(void);

// FUNCTION: SADX 0x0046c680
long ALO_GetRadicaseListenPos(struct NJS_POINT3 *pPos)
{
	struct NJS_POINT3 *var1;
	float var2;
	float var3;
	int var4;

	if (DAT_05b32e50 == 0)
		return 0;
	var1 = (struct NJS_POINT3 *)*(int *)((char *)DAT_05b32e50 + 0x20);
	var2 = (float)rand() * 3.0517578e-5f;
	var2 = var2 * 3.0f + 10.0f;
	var3 = (float)rand() * 3.0517578e-5f;
	var4 = (int)((var3 * 80.0f - 40.0f) * 65536.0f / -360.0f);
	var4 = *(int *)((char *)var1 + 0x18) - var4;
	var4 += 0x8000;
	pPos->x = njSin(var4) * var2 + *(float *)((char *)var1 + 0x20);
	pPos->y = *(float *)((char *)var1 + 0x24);
	pPos->z = njCos(var4) * var2 + *(float *)((char *)var1 + 0x28);
	return 1;
}
