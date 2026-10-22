#include "decls.h"
void DrawVal(long val, long keta, unsigned char zflg, float x, float y, float z, float mag);

// FUNCTION: SADX 0x0059eec0
int FUN_0059eec0(int param_1)
{
	int local_8 = 0;
	do
	{
		param_1 /= 10;
		local_8++;
	} while (param_1 != 0);
	return local_8;
}

// FUNCTION: SADX 0x0059eef0
void DrawValLf(long val, float x, float y, float z)
{
	DrawVal(val, FUN_0059eec0(val), 1, x, y, z, 1.0f);
}

// STUB: SADX 0x0059f060
void DrawValTrialLf(long val, float x, float y, float z, float magx, float magy)
{
}

// FUNCTION: SADX 0x0059f0b0
void DrawEbmlem(float x, float y, float z)
{
	___njSetTexture(&texlist_ava_emblem);
	ghSetPvrTexMaterial(0xffffffff);
	ghDrawPvrTexture(0x4000000, x * ScreenRaitoX, y * ScreenRaitoY, z, ScreenRaitoX, ScreenRaitoY);
}

// STUB: SADX 0x0059f120
void DrawMetalEbmlem(float x, float y, float z)
{
}
