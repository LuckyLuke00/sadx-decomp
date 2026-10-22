#include "decls.h"
extern float TARAI_Y;
void TaraiDisp(struct task *tp);
void TaraiExec(struct task *tp);

// STUB: SADX 0x006a5790
void BadeffExec(struct task *tp)
{
}

// FUNCTION: SADX 0x006a5810
void TaraiInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y = TARAI_Y;
	var1->mode = 0x13;
	var1->wtimer = 0;
	tp->exec = TaraiExec;
	tp->disp = TaraiDisp;
}

// FUNCTION: SADX 0x006a5840
void TateTaraiInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y = TARAI_Y;
	var1->wtimer = 0;
	var1->mode = 0x11;
	tp->exec = TateTaraiExec;
	tp->disp = TateTaraiDisp;
}

// FUNCTION: SADX 0x006a5870
void HugeTaraiInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y = TARAI_Y;
	var1->wtimer = 0;
	var1->mode = 0x14;
	tp->exec = HugeTaraiExec;
	tp->disp = HugeTaraiDisp;
}

// FUNCTION: SADX 0x006a58a0
void FUN_006a58a0(float param_1, float param_2, float param_3)
{
	struct task *var1 = CreateElementalTask(2, 3, BadeffExec);
	struct taskwk *var2 = var1->twp;
	var2->pos.x = param_1;
	var2->pos.y = param_2;
	var2->pos.z = param_3;
	var2->counter.f = -1.0f;
	var2->timer.f = 0.05f;
	var1->disp = BadeffDisp;
}

// STUB: SADX 0x006a5d10
void ButtonInit(struct task *tp)
{
}
