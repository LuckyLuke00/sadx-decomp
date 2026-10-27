#include "decls.h"
void ScoreInit();
void ScoreDisp(struct task *tp);
extern struct NJS_SPRITE DAT_03710f14;
extern char DAT_03710ecc[1];
extern float ScreenRaitoX;
extern float ScreenRaitoY;
extern int DAT_05b3ec18;
extern float DAT_060ce43c;
extern int DAT_060ce404;
extern int DAT_060ce440;
extern int DAT_060ce444;

// STUB: SADX 0x007eae60
void ScoreInit()
{
}

// FUNCTION: SADX 0x007eaf20
void ScoreDisp(struct task *tp)
{
	struct NJS_SPRITE spr;

	DAT_05b3ea24 = 0xff;
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 6);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	spr = DAT_03710f14;
	CalcScreenRaito_SPR2D_CR(&spr);
	DAT_060eea04.sx = ScreenRaitoX;
	DAT_060eea04.sy = ScreenRaitoY;
	late_DrawSprite2D(&DAT_060eea04, 0, 22047.0f, 0x22, 4);
	FUN_0055de60((struct _SC_NUMBERS *)DAT_03710ecc);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	ResetMaterial();
}

// FUNCTION: SADX 0x007eaff0
void ShtScoreAdd(int Score, struct taskwk *twp)
{
	struct task *var1 = twp->cwp->hit_cwp->mytask;
	if (var1->exec == Tama1)
	{
		DAT_060ce404 += Score * DAT_060ce440;
		DAT_060ce440++;
		if (DAT_060ce440 > 10)
		{
			DAT_060ce440 = 10;
		}
		DAT_060ce444 = 0x3c;
	}
	if (DAT_060ce404 >= 99999)
	{
		DAT_060ce404 = 99999;
	}
	DAT_05b3ec18 = DAT_060ce404;
}

// FUNCTION: SADX 0x007eb060
void HitNumAdd(void)
{
	DAT_060ce43c += 1.0;
}

// FUNCTION: SADX 0x007eb080
void ShtBossScoreAdd(int time)
{
	if (time < 0x708)
	{
		DAT_060ce404 += 0x7d0;
		DAT_05b3ec18 = DAT_060ce404;
		return;
	}
	if (time < 0xe10)
	{
		DAT_060ce404 += 0x3e8;
		DAT_05b3ec18 = DAT_060ce404;
		return;
	}
	if (time < 0x1518)
	{
		DAT_060ce404 += 0x1f4;
		DAT_05b3ec18 = DAT_060ce404;
	}
}

// STUB: SADX 0x007eb0e0
void ShtScoreTask(struct task *tp)
{
}
