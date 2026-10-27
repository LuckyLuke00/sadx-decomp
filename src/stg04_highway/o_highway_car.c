#include "decls.h"
extern float DAT_060cf070;
extern float DAT_060cf074;
extern float DAT_060cf078;
extern float DAT_060cf07c;
extern float DAT_060cf080;
extern struct NJS_TEXLIST *DAT_060cf088;
extern struct NJS_TEXANIM *DAT_060cf08c;

// FUNCTION: SADX 0x0081a940
void ObjectCarManagerExit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	FreeTaskC(tp);
	if ((var1->smode & 0x80) != 0)
	{
		dsStop_id((int)var1);
	}
}

// STUB: SADX 0x0081c0f0
void ObjectCarExit(struct task *tp)
{
}

// STUB: SADX 0x0081c250
void ObjectHighwayCar(struct task *tp)
{
}

// FUNCTION: SADX 0x0081c430
void ObjectHighwayCarManager(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	DAT_060cf07c = 0.2f;
	DAT_060cf080 = 0.2f;
	DAT_060cf088 = &texlist_car_light;
	DAT_060cf070 = 0.0f;
	DAT_060cf08c = (struct NJS_TEXANIM *)&anim_car_light;
	DAT_060cf074 = 0.0f;
	DAT_060cf078 = 0.0f;
	CreateCar(tp);
	var1->smode = 0;
	var1->wtimer = 0;
	*(int *)((char *)var1 + 8) = (int)tp->ctp;
	tp->dest = ObjectCarManagerExit;
	tp->exec = ObjectCarManagerRegular;
}
