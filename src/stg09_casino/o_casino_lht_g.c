#include "decls.h"

// FUNCTION: SADX 0x00873050
void ObjectCasinoLhtG(struct task *tp)
{
	struct taskwk *var1;
	long var2;

	var1 = tp->twp;
	var2 = CheckRangeOutWithR(tp, 360010.0f);
	if (var2 != 0)
	{
		return;
	}
	var1->wtimer = (short)var2;
	var1->mode = 1;
	tp->disp = (void (__cdecl *)(struct task *))0x872e10;
	tp->exec = (void (__cdecl *)(struct task *))0x872ef0;
	tp->dest = (void (__cdecl *)(struct task *))0x872e00;
	ObjCasino_InitTexAnimInfo(texanim, 2);
}
