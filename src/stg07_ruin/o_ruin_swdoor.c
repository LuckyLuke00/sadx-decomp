#include "decls.h"
extern struct obj *obj_sw[3];
extern struct CCL_INFO c_info_switch[1];

// FUNCTION: SADX 0x00852c90
void SwitchDisp(struct task *tp)
{
	struct taskwk *var1;
	struct obj *var2;
	struct obj *var3;

	var1 = tp->twp;
	___njSetTexture(&texlist_sw_panel);
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	var2 = obj_sw[var1->btimer];
	___dsDrawModel(var2->model);
	var3 = var2->child;
	FUN_0067d830(NULL, var3->pos[0], var3->pos[1], var3->pos[2]);
	if (var1->counter.f != 0.0f)
	{
		FUN_0067d830(NULL, 0.0f, var1->counter.f, 0.0f);
	}
	___dsDrawModel(var3->model);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00853220
void SwitchInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->mode = 0;
	CCL_Init(tp, c_info_switch, 1, 4);
	tp->exec = SwitchExec;
	tp->disp = SwitchDisp;
}
