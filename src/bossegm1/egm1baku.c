#include "decls.h"
extern struct task *DAT_060b99f0;
void egm1bakuhatsu_exec(struct task *tp);

// FUNCTION: SADX 0x006c4260
void SetEgm1Bakuhatsu(struct NJS_POINT3 *posp)
{
	struct task *var1;
	struct anywk *var2;
	var1 = CreateElementalTask(0, 3, egm1bakuhatsu_exec);
	DAT_060b99f0 = var1;
	if (var1 != 0)
	{
		var2 = (struct anywk *)CAlloc(1, 0xc);
		var1->awp = var2;
		var2->work.ptr[0] = posp;
		var2->work.ul[1] = 0;
		var2->work.ul[2] = 0;
		var1->exec = egm1bakuhatsu_exec;
	}
}

// FUNCTION: SADX 0x006c43b0
void InitEgm1DeadFly(struct task *tp)
{
	*(unsigned long *)((char *)tp->awp + 0x38) = 0;
}
