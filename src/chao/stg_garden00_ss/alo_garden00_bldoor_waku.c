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
	FUN_004a7cb0((struct obj *)&object_stch_bldoor_waku_waku, (struct NJS_MOTION *)&motion_stch_bldoor_waku, *(float *)((char *)var1 + 0x2c));
	npSetZCompare();
	njPopMatrixEx();
}

// STUB: SADX 0x00477720
struct task *AloG00BldoorWakuCreate(struct task *parent_tp)
{
	return (struct task *)0;
}
