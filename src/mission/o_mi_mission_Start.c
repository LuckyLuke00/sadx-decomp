#include "decls.h"

extern unsigned char DAT_05b37311;
extern unsigned char *DAT_05b37314;
extern unsigned char DAT_05b37318;
extern struct CCL_INFO mission01_colli_info[];
extern struct NJS_ACTION action_mi_ssobj_card[];

// STUB: SADX 0x0049d140
static void Disp(struct task *tp)
{
}

// FUNCTION: SADX 0x0049d1c0
static void Destructor(struct task *tp)
{
	ReleaseMiMessage();
}

// STUB: SADX 0x0049d1d0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0049d390
void ObjectMiMission_Start(struct task *tp)
{
	struct OBJ_CONDITION *var1 = tp->ocp;
	struct taskwk *var2 = tp->twp;
	if (IsMissionAppear(tp))
	{
		if (DAT_05b37311 < 60 && DAT_05b37314[**(unsigned char **)((char *)var1 + 0x10)] & 0x80)
		{
			return;
		}
		if (DAT_05b37318 != **(unsigned char **)((char *)var1 + 0x10))
		{
			var2->ang.x = 0;
			var2->ang.z = 0;
			var2->mode = 1;
			CCL_Init(tp, mission01_colli_info, 1, 4);
			var2->counter.ptr = action_mi_ssobj_card;
			tp->exec = Exec;
			tp->disp = Disp;
			tp->dest = Destructor;
		}
	}
}
