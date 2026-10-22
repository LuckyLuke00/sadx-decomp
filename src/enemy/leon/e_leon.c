#include "decls.h"
void FUN_005c09e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005c0a60(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005c0b80(struct taskwk *param_1, struct enemywk *param_2);

// FUNCTION: SADX 0x005c09e0
void FUN_005c09e0(struct taskwk *param_1, struct enemywk *param_2)
{
	FUN_005c0b80(param_1, param_2);
	FUN_005c0a60(param_1, param_2);
	FUN_008d8710(param_1, param_2);
	LeonDraw(param_1, param_2);
	if (EnemyDist2FromPlayer(param_1, 0) < 90000.0f)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 1;
		param_1->wtimer = 0;
	}
}

// STUB: SADX 0x005c0a60
void FUN_005c0a60(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c0b80
void FUN_005c0b80(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c1a30
void FUN_005c1a30(int param_1)
{
}

// STUB: SADX 0x005c1a90
void LeonWalk(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c1d30
void LeonTurnHead(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c2840
void LeonDecideAim(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c2970
void LeonAttack(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005c2a80
void FUN_005c2a80(struct task *tp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005c2b10
void CallLeonDraw(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	LeonDraw(local_cg, local_8g);
}

// FUNCTION: SADX 0x005c2b40
void CallLeonDrawLink(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	LeonDrawLink(local_cg, (struct enemywk *)local_8g);
}
