#include "decls.h"
extern struct task *DAT_060dc4cc;
extern struct task *DAT_060dc4c8;

// FUNCTION: SADX 0x0088c400
void ObjectCasinoMizuEnd(struct task *tp)
{
	struct task *var1 = DAT_060dc4cc;
	while (var1 != 0)
	{
		struct task *var2 = (struct task *)var1->mwp;
		struct task *var3 = (struct task *)var1->fwp;
		struct task *var4 = var3;
		if (var2 == 0)
		{
			DAT_060dc4cc = var3;
		}
		else
		{
			*(struct task **)((char *)var2 + 0x28) = var3;
		}
		var3 = (struct task *)var1->fwp;
		if (var3 != 0)
		{
			*(struct task **)((char *)var3 + 0x24) = (struct task *)var1->mwp;
		}
		Free(var1);
		var1 = var4;
	}
	if (DAT_060dc4c8 == tp)
	{
		DAT_060dc4c8 = 0;
	}
}

// STUB: SADX 0x0088c460
void ObjectCasinoMizuDraw(struct task *tp)
{
}

// STUB: SADX 0x0088c640
void MizuSmoke1(float x, float y, float z, float spd)
{
}

// STUB: SADX 0x0088c720
void MizuSmoke2(float x, float y, float z, float spd)
{
}

// FUNCTION: SADX 0x0088ce20
void ObjectCasinoMizu1(struct task *tp)
{
	tp->disp = ObjectCasinoMizuDraw;
	tp->exec = ObjectCasinoMizuExec;
	tp->dest = ObjectCasinoMizuEnd;
}
