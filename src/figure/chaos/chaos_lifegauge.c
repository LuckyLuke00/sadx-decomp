#include "decls.h"
extern unsigned char DAT_05edc418;
extern unsigned char DAT_05edc419;
extern float DAT_05edc424;
extern float ScreenRaitoX;
extern float ScreenRaitoY;
extern int DAT_05b9d838;
extern signed char DAT_05b3ea16;
void late_SetFunc(void (*fnc)(void *), void *arg, float zprio, int flgs);
void late_ChaosLifeGaugeDisplay(struct task *tp);

// STUB: SADX 0x005d11a0
void SetChaosLifeGauge(int xpos, int ypos, int max)
{
}

// STUB: SADX 0x005d1230
void ChaosLifeGauge(struct task *tp)
{
}

// FUNCTION: SADX 0x005d13f0
void ChaosLifeGaugeDisplay(struct task *tp)
{
	if (DAT_05b9d838)
		return;
	if (DAT_05b3ea16 < 0)
		return;
	late_SetFunc((void (*)(void *))late_ChaosLifeGaugeDisplay, tp, 22047.990234375f, 1);
}

// FUNCTION: SADX 0x005d18e0
void SetChaosLifeGaugeC(int xpos, int ypos, int max, struct task *ptp)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	local_cg = CreateChildTask(2, ChaosLifeGauge, ptp);
	local_8g = local_cg->twp;
	if (xpos > 0)
	{
		local_8g->pos.x = (float)xpos;
		local_8g->pos.y = (float)ypos;
	}
	else
	{
		local_8g->pos.x = ScreenRaitoX * 600.0f - 35.0f;
		local_8g->pos.y = ScreenRaitoY * 48.0f + 10.0f;
	}
	DAT_05edc418 = (unsigned char)max;
	DAT_05edc419 = DAT_05edc418;
	DAT_05edc424 = (float)max;
}
