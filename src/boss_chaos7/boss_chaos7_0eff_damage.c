#include "decls.h"

// STUB: SADX 0x007014b0
void Display(struct task *tp)
{
}

// FUNCTION: SADX 0x00701530
void NormalD(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = var1->counter.f + 0.3333333432674408;
	if (var1->counter.f >= 16.0)
	{
		FreeTask(tp);
	}
	else
	{
		Display(tp);
	}
}

// FUNCTION: SADX 0x00701570
void Sprite_Chaos7Damage(struct task *tp)
{
	tp->exec = NormalD;
	tp->disp = Display;
	tp->twp->counter.f = 0.0f;
}

// STUB: SADX 0x00701620
void NormalS2(struct task *tp)
{
}

// FUNCTION: SADX 0x00701660
void Sprite_Chaos7DamageS2(struct task *tp)
{
	tp->exec = NormalS2;
	tp->disp = DisplayS;
	tp->twp->timer.l = 0;
}

// STUB: SADX 0x00701950
void NormalMist(struct task *tp)
{
}

// STUB: SADX 0x00701c50
void SetMistDisplayTask(struct task *tp)
{
}

// STUB: SADX 0x00701dd0
void objNormalR(struct task *tp)
{
}

// FUNCTION: SADX 0x00701e30
void Chaos7NodamageEffect(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->timer.b[0] = 3;
	tp->exec = objNormalR;
	tp->disp = objDisplayR;
}
