#include "decls.h"
extern void *DAT_060dc4d0;
extern void *DAT_060dc4d4;

// FUNCTION: SADX 0x0088d030
void ObjectCasino_eff_kinka1_End(struct task *tp)
{
	struct task *var1 = (struct task *)DAT_060dc4d4;
	while (var1 != 0)
	{
		struct task *var2 = *(struct task **)((char *)var1 + 0x3c);
		struct task *var3 = *(struct task **)((char *)var1 + 0x40);
		struct task *var4 = var3;
		if (var2 == 0)
		{
			DAT_060dc4d4 = var3;
		}
		else
		{
			*(struct task **)((char *)var2 + 0x40) = var3;
		}
		var3 = *(struct task **)((char *)var1 + 0x40);
		if (var3 != 0)
		{
			*(struct task **)((char *)var3 + 0x3c) = *(struct task **)((char *)var1 + 0x3c);
		}
		Free(var1);
		var1 = var4;
	}
	if (DAT_060dc4d0 == tp)
	{
		DAT_060dc4d0 = 0;
	}
}

// FUNCTION: SADX 0x0088d4f0
void ObjectCasino_eff_kinka1(struct task *tp)
{
	tp->disp = ObjectCasino_eff_kinka1_Draw;
	tp->exec = ObjectCasino_eff_kinka1_Exec;
	tp->dest = ObjectCasino_eff_kinka1_End;
}
