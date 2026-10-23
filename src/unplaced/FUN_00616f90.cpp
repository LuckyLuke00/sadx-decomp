#include "decls.h"
extern int DAT_05edeecc;
extern int DAT_05edeed0;
extern int DAT_05edeed4;
extern int DAT_05edecac;
extern int DAT_05edecb0;
extern int DAT_05edecb4;
extern short DAT_05edece8;
extern short DAT_05edecec;
extern int DAT_05eded7c;

// FUNCTION: SADX 0x00616f90
void FUN_00616f90(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	DAT_05eded7c = 1;
	DAT_05edecac = DAT_05edeecc;
	DAT_05edecb0 = DAT_05edeed0;
	DAT_05edecb4 = DAT_05edeed4;
	CreateElementalTask(2, 6, Eggrob_LockOnCursor);
	local_8->timer.l = 0xb4;
	DAT_05edecec = 9;
	local_8->mode = 0x12;
	PSetMotion((struct mtnjvwk *)&DAT_05edece8);
	local_8->value.f = 1.0f;
	Eggrob_Display(param_1);
	Shadow(local_8, 1.8f);
	param_1->exec = EggrobForEvent0_RP_1;
}
