#include "decls.h"
extern struct NJS_TEXLIST texlist_gachapon;
extern struct obj DAT_05a862dc;

// STUB: SADX 0x0088e830
void GachaSetPosition(struct taskwk *twp, struct gachamotionwk *mwp)
{
}

// STUB: SADX 0x0088eb50
int FUN_0088eb50(void *param_1, void *param_2)
{
	return (int)0;
}

// FUNCTION: SADX 0x0088ed40
void GachaponDestructor(struct task *tp)
{
	if (tp->mwp != NULL)
	{
		Free(tp->mwp);
		tp->mwp = NULL;
	}
}

// FUNCTION: SADX 0x0088f7a0
void GachaponPartsDisplayer(struct task *tp)
{
	struct motionwk *var1 = tp->mwp;
	struct taskwk *var2 = tp->twp;

	___njSetTexture(&texlist_gachapon);
	njPushMatrix(0);
	njTranslateV(0, &var2->pos);
	njRotateZXY(0, (long *)(*(long *)&var2->ang.x), (long *)(*(long *)&var2->ang.y), (long *)(*(long *)&var2->ang.z));
	___dsDrawModel((struct NJS_MODEL *)var2->value.l);
	njPopMatrix(1);
	SetRegularTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var2->pos.x, var1->height + 0.5, var2->pos.z);
	late_DrawShadowObject(&DAT_05a862dc, 1.0);
	njPopMatrix(1);
}

// STUB: SADX 0x008902b0
void InitGachaponTask(struct task *tp)
{
}

// STUB: SADX 0x008903d0
void GachaponManager(struct task *tp)
{
}

// STUB: SADX 0x008909c0
void GachaponGenerateAsChildTask(struct task *tp, struct gacha_cmd *cmd)
{
}
