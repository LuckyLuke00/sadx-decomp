#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern "C" int rand(void);

// STUB: SADX 0x0049ca40
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x0049cb90
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0049cda0
void ObjectMiBaloon(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		*(int *)((char *)var1 + 0x14) = 0;
		*(int *)((char *)var1 + 0x1c) = 0;
		float var2 = (float)rand() * 3.0517578125e-05;
		*(int *)((char *)var1 + 8) = (unsigned int)(var2 * 100.0);
		CCL_Init(tp, mi_baloon_colli_info, 2, 4);
		tp->exec = Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Disp;
	}
}
