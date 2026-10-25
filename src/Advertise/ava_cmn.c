#include "decls.h"
void DrawValTrialS(long val, long keta, unsigned char zflg, float x, float y, float z, float magx, float magy);
extern float ScreenRaitoX;
extern float ScreenRaitoY;
extern int FUN_0059eec0(int param_1);
extern unsigned char DAT_05cd14ea;
extern unsigned char MChPvrIdx[7];
void DrawVal(long val, long keta, unsigned char zflg, float x, float y, float z, float mag);

// FUNCTION: SADX 0x0059eac0
void DrawMCharName(enum AvaCharEnum chnum, unsigned long col, float x, float y, float z, float magx, float magy)
{
	if (chnum == 6 && DAT_05cd14ea == 1)
	{
		___njSetTexture(&texlist_ava_metal);
		ghSetPvrTexMaterial(col);
		ghDrawPvrTexture(0x4000002, x * ScreenRaitoX, y * ScreenRaitoY, z, magx * ScreenRaitoX, magy * ScreenRaitoY);
	}
	else
	{
		___njSetTexture(&texlist_m_chnam);
		ghSetPvrTexMaterial(col);
		ghDrawPvrTexture((MChPvrIdx[chnum] | 0x4000000), x * ScreenRaitoX, y * ScreenRaitoY, z, magx * ScreenRaitoX, magy * ScreenRaitoY);
	}
}

// STUB: SADX 0x0059ed90
void DrawVal(long val, long keta, unsigned char zflg, float x, float y, float z, float mag)
{
}

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

// STUB: SADX 0x0059ef30
void DrawValTrialS(long val, long keta, unsigned char zflg, float x, float y, float z, float magx, float magy)
{
}

// FUNCTION: SADX 0x0059f060
void DrawValTrialLf(long val, float x, float y, float z, float magx, float magy)
{
	DrawValTrialS(val, FUN_0059eec0(val), 1, x, y, z, magx, magy);
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

// FUNCTION: SADX 0x0059f1a0
void DrawSankaku(int muki, float x, float y, float z)
{
	muki = (muki != 0 ? 0x46000000 : 0) + 0x1000000;
	___njSetTexture(&texlist_ava_san);
	ghSetPvrTexMaterial(0xffffffff);
	ghDrawPvrTexture(muki | 1, x * ScreenRaitoX, y * ScreenRaitoY, z, ScreenRaitoX, ScreenRaitoY);
	ghDrawPvrTexture(muki, x * ScreenRaitoX, y * ScreenRaitoY, z + -0.30000001192092896, ScreenRaitoX, ScreenRaitoY);
}

// STUB: SADX 0x0059f490
void DrawTrialCartTime(struct CLEAR_TIME *clp, float x, float y, float z)
{
}
