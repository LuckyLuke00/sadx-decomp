#include "decls.h"

// GLOBAL: SADX 0x026dcba8
static struct CCL_INFO obj_c_info[4];

static void Exec(struct task *tp);
static void disp(struct task *tp);
extern "C" double fabs(double param_1);

// STUB: SADX 0x00685f10
static void disp(struct task *tp)
{
}

// STUB: SADX 0x00686080
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00686240
void ObjectSSHiddendoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float var2;

	var1->counter.f = 0.0f;
	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->wtimer = (unsigned short)fabs(var1->scl.x);
	var2 = fabs(var1->scl.y);
	var1->value.l = (int)var2;
	FUN_0058b860(var1->wtimer, 0);
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, &obj_c_info[0], 4, 4);
	}
	tp->exec = Exec;
	tp->disp = disp;
}
