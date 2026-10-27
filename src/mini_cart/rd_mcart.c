#include "decls.h"
static void deadRound(struct task *task_p);
static void initRound(struct task *task_p, const void *param_p);
static void execRound(struct task *task_p);
extern struct TaskInfo RdTaskInfo;

// FUNCTION: SADX 0x007e43a0
void Rd_MiniCart(struct task *task_p)
{
	MirenInitTask(task_p, &RdTaskInfo, 0);
}

// FUNCTION: SADX 0x007e43c0
static void execRound(struct task *task_p)
{
	struct motionwk *var1;
	int var2;
	SetFreeCameraMode(0);
	var1 = task_p->mwp;
	switch (var1->work.b[0])
	{
	case 0:
		CartRaceSetManageTask();
		SetCartCameraDemo();
		InitStartDushCheck();
		PadReadOn();
		PadReadOffP(0);
		PauseEnable();
		CartActInitActDiff();
		var1->work.b[0] = 1;
		dsInitInt(1, 1);
		break;
	case 1:
		var2 = CartActGetActDiff();
		if (var2 != 0)
		{
			CartRaceDestroyManageTask();
			MirenGameChangeAct(var2, 0x19);
			var1->work.b[0] = 0;
		}
		SetTime(5, 0);
		break;
	}
}

// FUNCTION: SADX 0x007e4450
static void deadRound(struct task *task_p)
{
	ResetMleriRangeRad();
}

// FUNCTION: SADX 0x007e4460
static void initRound(struct task *task_p, const void *param_p)
{
	struct task *var1;
	*(char *)task_p->mwp = 0;
	var1 = CreateElementalTask(2, 0, mc_bgmcontrol);
	var1->twp->mode = 0x19;
	var1->twp->wtimer = 0xa;
	InitSnatchPlayerInfo();
	SetMleriRangeRad(2000.0f);
	InitStartDushCheck();
	execRound(task_p);
}

// FUNCTION: SADX 0x007f2e70
void mc_bgmcontrol(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	var1->wtimer--;
	if ((short)var1->wtimer < 0)
	{
		CreateElementalTask(0, 1, ADX_TaskInit);
		BGM_Play(var1->mode);
		DestroyTask(tp);
	}
}

// GLOBAL: SADX 0x00a098cc
struct TaskInfo RdTaskInfo = {1, 2, (void (*)(struct task *, void *))initRound, execRound, 0, deadRound};
