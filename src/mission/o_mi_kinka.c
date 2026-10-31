#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// STUB: SADX 0x0049c460
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x0049c4f0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0049c780
void ObjectMiKinka(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		*(int *)((char *)var1 + 0x14) = 0;
		*(int *)((char *)var1 + 0x1c) = 0;
		CCL_Init(tp, mi_kinka_colli_info, 1, 4);
		tp->exec = Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Disp;
	}
}
