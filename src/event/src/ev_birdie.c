#include "decls.h"
extern struct CCL_INFO cinfo[1];
static void ev_birdie_exec(struct task *tp, struct MJOIN_VERTEX *pj);
extern struct MJOIN_VERTEX pj0[1];
extern struct MJOIN_VERTEX pj2[1];
extern struct MJOIN_VERTEX pj1[1];

// FUNCTION: SADX 0x007d5820
static void ev_birdie_exec(struct task *tp, struct MJOIN_VERTEX *pj)
{
	struct eventwk *var1 = tp->twp->ewp;
	struct EVENT_ACTION_LIST *var2 = (struct EVENT_ACTION_LIST *)*(int **)((char *)var1 + 0x40);
	if (var2 != NULL)
	{
		MJoinVertexes(*(struct obj **)((char *)var2 + 8), *(struct NJS_MOTION **)((char *)var2 + 4), *(float *)((char *)var1 + 0x3c), pj);
	}
	___dsSetPalette(2);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	EventObject(tp);
	ResetMaterial();
	___dsSetPalette(0);
}

// FUNCTION: SADX 0x007d5880
void ev_birdie0_exec(struct task *tp)
{
	ev_birdie_exec(tp, &pj0[0]);
}

// FUNCTION: SADX 0x007d58a0
void ev_birdie1_exec(struct task *tp)
{
	ev_birdie_exec(tp, &pj1[0]);
}

// FUNCTION: SADX 0x007d58c0
void ev_birdie2_exec(struct task *tp)
{
	ev_birdie_exec(tp, &pj2[0]);
}

// STUB: SADX 0x007d58e0
struct task *SetEventBirdie0(void)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x007d5910
struct task *SetEventBirdie1(void)
{
	struct task *var1 = CreateElementalTask(2, 5, ev_birdie1_exec);
	SetEventWork(var1->twp);
	CCL_Init(var1, cinfo, 1, 4);
	return var1;
}

// FUNCTION: SADX 0x007d5940
struct task *SetEventBirdie2()
{
	struct task *var1 = CreateElementalTask(2, 5, ev_birdie2_exec);
	SetEventWork(var1->twp);
	CCL_Init(var1, &cinfo[0], 1, 4);
	return var1;
}
