#include "decls.h"
extern void *DAT_060dbbf0;
extern struct task *DAT_060dbbec;

// FUNCTION: SADX 0x00868f20
void ObjectIcecap_eff_lines1_End(struct task *tp)
{
	void *var1 = DAT_060dbbf0;
	while (var1 != 0)
	{
		void *var2 = *(void **)((char *)var1 + 0x14);
		void *var3 = *(void **)((char *)var1 + 0x18);
		void *var4 = var3;
		if (var2 == 0)
		{
			DAT_060dbbf0 = var3;
		}
		else
		{
			*(void **)((char *)var2 + 0x18) = var3;
		}
		var3 = *(void **)((char *)var1 + 0x18);
		if (var3 != 0)
		{
			*(void **)((char *)var3 + 0x14) = *(void **)((char *)var1 + 0x14);
		}
		Free(*(void **)((char *)var1 + 4));
		Free(*(void **)var1);
		Free(*(void **)((char *)var1 + 8));
		Free(var1);
		var1 = var4;
	}
	if (DAT_060dbbec == tp)
	{
		DAT_060dbbec = 0;
	}
}

// FUNCTION: SADX 0x008691c0
void ObjectIcecap_eff_lines1(struct task *tp)
{
	tp->exec = ObjectIcecap_eff_lines1_Exec;
	tp->dest = ObjectIcecap_eff_lines1_End;
}
