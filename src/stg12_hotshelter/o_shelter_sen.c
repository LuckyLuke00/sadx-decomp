#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x008b4340
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008b4440
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008b4730
void ObjShelterSen(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;

	var1->pos.x = 750.0f;
	var1->ang.x = 0;
	var1->pos.y = 75.5f;
	var1->ang.y = 0;
	var1->ang.z = 0;
	var1->pos.z = -650.0f;
	var1->counter.f = 0.0f;
	var2->spd.x = 0.0f;
	var2->spd.y = 0.0f;
	var2->spd.z = 0.0f;
	if (GetPlayerCharacterName(0) == 7)
	{
		var1->mode = 1;
		tp->exec = Exec;
		tp->disp = Disp;
	}
	else
	{
		var1->mode = 0;
		tp->exec = ExecNotBig;
		tp->disp = Disp;
	}
}
