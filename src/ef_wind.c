#include "decls.h"
void BlowingWind(struct task *tp);
extern "C" int rand(void);
void StopBlowingWind(struct task *tp);
extern struct task *DAT_05edcc38;

// FUNCTION: SADX 0x005da830
void SetWind(unsigned char str, long *pAngy)
{
	struct task *local_8g;
	int local_cj;
	float local_10;

	if (DAT_05edcc38 == 0)
	{
		local_8g = CreateElementalTask(2, 0, BlowingWind);
		if (local_8g == 0)
		{
			return;
		}
		local_8g->dest = StopBlowingWind;
		DAT_05edcc38 = local_8g;
		local_cj = rand();
		local_10 = (float)local_cj / 32768.0;
		local_8g->twp->ang.y = (long)(local_10 * 65535.0);
		local_8g->twp->pos.x = -100000.0f;
		local_8g->twp->pos.y = 0.0f;
		local_8g->twp->pos.z = -100000.0f;
	}
	DAT_05edcc38->twp->smode = str;
	if (pAngy != 0)
	{
		DAT_05edcc38->twp->ang.y = *pAngy;
	}
}

// FUNCTION: SADX 0x005da900
void StopWind()
{
	if (DAT_05edcc38 != 0)
	{
		DestroyTask(DAT_05edcc38);
		DAT_05edcc38 = 0;
	}
}

// FUNCTION: SADX 0x005da930
void StopBlowingWind(struct task *tp)
{
	DAT_05edcc38 = 0;
}

// STUB: SADX 0x005daab0
long GetWindStatus(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec)
{
	return (long)0;
}
