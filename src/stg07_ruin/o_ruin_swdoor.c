#include "decls.h"
extern struct CCL_INFO c_info_switch[1];

// STUB: SADX 0x00852c90
void SwitchDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x00853220
void SwitchInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->mode = 0;
	CCL_Init(tp, c_info_switch, 1, 4);
	tp->exec = SwitchExec;
	tp->disp = SwitchDisp;
}
