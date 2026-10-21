#include "decls.h"
extern int DAT_05b9d838;
extern signed char DAT_05b3ea16;
void late_SetFunc(void (*fnc)(void *), void *arg, float zprio, int flgs);
void late_ChaosLifeGaugeDisplay(struct task *tp);

// FUNCTION: SADX 0x005d13f0
void ChaosLifeGaugeDisplay(struct task *tp)
{
	if (DAT_05b9d838)
		return;
	if (DAT_05b3ea16 < 0)
		return;
	late_SetFunc((void (*)(void *))late_ChaosLifeGaugeDisplay, tp, 22047.990234375f, 1);
}
