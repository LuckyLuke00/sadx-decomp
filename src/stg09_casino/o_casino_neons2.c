#include "decls.h"
static void End(struct task *tp);
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// GLOBAL: SADX 0x0480b3c8
static struct TEXUVINFO texuvinfo[9];

// FUNCTION: SADX 0x008769e0
static void End(struct task *tp)
{
	ObjCasino_EndTexUvInfo(&texuvinfo[0], 9);
}

// STUB: SADX 0x008769f0
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x00876aa0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00876b20
void ObjectCasinoMain1fNeon(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) != 0)
	{
		return;
	}
	tp->disp = Disp;
	tp->exec = Exec;
	tp->dest = End;
	var1->wtimer = 0;
	var1->smode = 0;
	ObjCasino_InitTexUvInfo(texuvinfo, 9);
	FUN_004c39c0(tp);
}
