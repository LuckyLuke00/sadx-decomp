#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern void *DAT_060dc41c;
extern int DAT_060dc420;
extern long DAT_060dc408[5];

// FUNCTION: SADX 0x00874d80
long ObjCasino_GetFanStatus(signed char ID)
{
	if (ID < 5)
	{
		return DAT_060dc408[ID];
	}
	return 0;
}

// FUNCTION: SADX 0x008752f0
void EndKuzu(struct task *twp)
{
	struct taskwk *var1 = twp->twp;

	if (var1->counter.l != 0)
	{
		if (DAT_060dc41c != 0)
		{
			if (--DAT_060dc420 == 0)
			{
				Free(DAT_060dc41c);
				DAT_060dc41c = 0;
			}
		}
		var1->counter.l = 0;
	}
}

// STUB: SADX 0x00875330
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x008753c0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00875a30
void ObjectCasinoFanfan(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 2250000.0f) == 0)
	{
		var1->mode = 0;
		var1->value.f = 0.0f;
		var1->wtimer = 0;
		var1->timer.w[0] = 0;
		var1->counter.l = 0;
		tp->exec = Exec;
		tp->disp = Disp;
		tp->dest = (void (__cdecl *)(struct task *))EndKuzu;
	}
}
