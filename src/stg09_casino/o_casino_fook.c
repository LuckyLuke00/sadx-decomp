#include "decls.h"

// GLOBAL: SADX 0x0480b064
static struct CCL_INFO object_c_info[1];

static void Exec(struct task *tp);
static void Disp(struct task *tp);
void ObjectCasinoFook(struct task *tp);

// STUB: SADX 0x008749b0
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x00874a70
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00874c40
void ObjectCasinoFook(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 490010.0f) == 0)
	{
		tp->disp = Disp;
		tp->exec = Exec;
		tp->dest = ObjectCasinoManfEnd;
		if (FUN_004c39c0(tp) == 0)
		{
			var1->ang.x = 0;
			var1->ang.z = 0;
			CCL_Init(tp, &object_c_info[0], 1, 4);
			ObjCasino_InitGColl(tp, &object_cas_fook_fook[0], 80.0f, 0);
		}
	}
}
