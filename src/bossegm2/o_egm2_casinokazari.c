#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern struct obj object_casinoobj_builg_builg[1];

#pragma optimize("", off)
// STUB: SADX 0x006c70e0
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x006c7340
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006c75a0
void BuilGInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->mode = 0;
	var1->wtimer = 0;
	var1->btimer = 0;
	ResetMatAttribute(&object_casinoobj_builg_builg[0], 0xfdffffff);
	tp->exec = BuilGExec;
	tp->disp = BuilGDisp;
}

// FUNCTION: SADX 0x006c75e0
void ObjectEgm2Casinokazari(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->ang.x = 0;
	var1->ang.y = 0;
	var1->ang.z = 0;
	var1->mode = 1;
	var1->wtimer = (short)(DAT_05b9d724 << 8 | DAT_05b9d744);
	var1->smode = 0;
	var1->timer.l = 0;
	CreateChildTask(2, BuilGInit, tp);
	ResetMatAttribute(&object_casinoobj_casinobuil_casinobuil[0], 0xfdffffff);
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = ExplosionRockDestructor;
}
