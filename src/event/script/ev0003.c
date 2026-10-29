#include "decls.h"
extern struct task *DAT_060cbf58;

// FUNCTION: SADX 0x007cd3f0
void tornado_disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	njPushMatrix(NULL);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	___njSetTexture(&texlist_ev_s_t2c_body);
	late_ActionClipMesh((struct NJS_ACTION *)&action_ev_s_t2c_body, var1->value.f, 0, 1.0f);
	FUN_0067d830((float *)0, 0.0f, 2.8f, -2.6f);
	njRotateY(NULL, 0x4000);
	___njSetTexture(&texlist_ev_s_t2c_body);
	ds_ActionClip((struct NJS_ACTION *)&action_m_with_tr2_miles, var1->counter.f, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007cd770
void tornado_cons(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	var1->value.f = 0.0f;
	var1->timer.f = 0.0f;
	var1->counter.f = 0.0f;
	var1->wtimer = 0;
	var1->scl.x = 0.0f;
	var1->ang.y = 0xbd22;
	var1->scl.y = 0.0f;
	var1->mode = 0;
	tp->exec = tornado_exec;
	tp->disp = tornado_disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007cd7b0
void FUN_007cd7b0()
{
	DAT_060cbf58 = CreateElementalTask(2, 5, tornado_cons);
}

// FUNCTION: SADX 0x007cd7d0
void FUN_007cd7d0()
{
	if (DAT_060cbf58)
	{
		FreeTask(DAT_060cbf58);
		DAT_060cbf58 = 0;
	}
}
