#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_stch_bldoor_waku_waku[1];
extern struct NJS_MOTION motion_stch_bldoor_waku[1];

// FUNCTION: SADX 0x004775a0
void AloG00BldoorWakuDisp(struct task *tp)
{
	struct taskwk *var1;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	var1 = tp->twp;
	njPushMatrixEx();
	FUN_0067d830((float *)0, -71.0f, 0.0f, 155.0f);
	___njSetTexture(&texlist_Garden00SSObj);
	FUN_00422560(3);
	FUN_004a7cb0((struct obj *)&object_stch_bldoor_waku_waku, (struct NJS_MOTION *)&motion_stch_bldoor_waku, var1->scl.x);
	npSetZCompare();
	njPopMatrixEx();
}

// FUNCTION: SADX 0x00477720
struct task *AloG00BldoorWakuCreate(struct task *parent_tp)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateChildTask(2, AloG00BldoorWakuExec, parent_tp);
	if (var1 != 0)
	{
		var2 = var1->twp;
		var2->pos.x = -71.0f;
		var2->ang.y = 0;
		var2->pos.y = 0.0f;
		var2->pos.z = 155.0f;
	}
	return var1;
}
