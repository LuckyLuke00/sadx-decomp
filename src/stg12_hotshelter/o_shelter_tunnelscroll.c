#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x008b5f70
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008b6060
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008b6190
void ObjShelterTunnelscroll(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->pos.x = 0.0f;
	var1->pos.y = 10000.0f;
	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->wtimer = DAT_05b9d724 << 8 | DAT_05b9d744;
	var1->counter.f = 0.0f;
	var1->timer.f = 20.0f;
	var1->mode = 2;
	tp->exec = Exec;
	tp->disp = Disp;
}
