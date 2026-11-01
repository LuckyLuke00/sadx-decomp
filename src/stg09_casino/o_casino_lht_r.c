#include "decls.h"
static void End(struct task *tp);
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// GLOBAL: SADX 0x0480a688
static struct TEXANIMINFO texanim[2];

// FUNCTION: SADX 0x008730a0
static void End(struct task *tp)
{
	FUN_007d21b0(&texanim[0], 2);
}

// STUB: SADX 0x008730b0
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x00873190
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008732f0
void ObjectCasinoLhtR(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) != 0)
	{
		return;
	}
	var1->wtimer = 0;
	var1->mode = 1;
	tp->disp = Disp;
	tp->exec = Exec;
	tp->dest = End;
	ObjCasino_InitTexAnimInfo(texanim, 2);
}
