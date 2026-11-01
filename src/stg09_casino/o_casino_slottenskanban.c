#include "decls.h"
static void End(struct task *tp);

// GLOBAL: SADX 0x0480bb34
static struct CCL_INFO object_c_info[1];

static void Exec(struct task *tp);
static void Disp(struct task *tp);

// GLOBAL: SADX 0x0480ba80
static struct TEXUVINFO texuvinfo[9];

// FUNCTION: SADX 0x00878690
static void End(struct task *tp)
{
	ObjCasino_EndTexUvInfo(&texuvinfo[0], 9);
}

// STUB: SADX 0x008786a0
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x00878760
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008787f0
void ObjectCasinoKanbanS(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		tp->disp = Disp;
		tp->exec = Exec;
		tp->dest = End;
		var1->wtimer = 0;
		var1->smode = 0;
		ObjCasino_InitTexUvInfo(&texuvinfo[0], 9);
		if (FUN_004c39c0(tp) == 0)
		{
			var1->ang.x = 0;
			var1->ang.z = 0;
			CCL_Init(tp, &object_c_info[0], 1, 4);
		}
	}
}
