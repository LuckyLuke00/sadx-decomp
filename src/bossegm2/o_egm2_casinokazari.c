#include "decls.h"
extern struct obj object_casinoobj_builg_builg[1];

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
