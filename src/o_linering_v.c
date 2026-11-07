#include "decls.h"
static void LineringInit(struct task *tp);
static void Exec(struct task *tp);

// FUNCTION: SADX 0x008ba1e0
void ObjectLineringV(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	local_cg->ang.z = 0;
	local_cg->mode = 0;
	local_cg->wtimer = 0;
	local_cg->mode = 0;
	LineringInit(tp);
	tp->exec = Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_008b9f60;
}

// STUB: SADX 0x008ba240
static void Exec(struct task *tp)
{
}

// STUB: SADX 0x008ba720
static void LineringInit(struct task *tp)
{
}
