#include "decls.h"
extern struct obj object_lwobj_lwswitch_button[1];
extern struct obj object_lwobj_lwswitch_lwswitch[1];
extern int DAT_05b9d838;
extern char DAT_060d131b;

// FUNCTION: SADX 0x00853ee0
void SwitchTerm(struct task *tp)
{
	DAT_060d131b--;
}

// FUNCTION: SADX 0x00853ef0
void SwitchDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	object_lwobj_lwswitch_button[0].pos[1] = var1->value.f;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	SetObjectTexture();
	ds_DrawObjectClip(&object_lwobj_lwswitch_lwswitch[0], 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00854100
void PanelTerm(struct task *tp)
{
	struct taskwk *var1;
	int var2;

	DAT_060d131b--;
	var1 = tp->twp;
	var2 = FUN_004c39c0(tp);
	if (var2 == 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->value.ptr);
		ReleaseMobileLandObject((struct obj *)var1->value.ptr);
		NpcMilesSetStandByFlag(0);
	}
}

// FUNCTION: SADX 0x00854790
void PanelExecEdit(struct task *tp)
{
	tp->twp->wtimer = tp->twp->ang.x;
	PanelExec(tp);
}
