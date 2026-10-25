#include "decls.h"
static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);

// FUNCTION: SADX 0x0068aed0
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	late_DrawModelClipMesh(model_poolparasol_poolparasol_poolparasol, 0, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068af40
static void ObjectMain(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) != 0)
	{
		ObjectDisplay(tp);
		return;
	}
	if (CheckRangeOut(tp) == 0)
	{
		ObjectDisplay(tp);
		EntryColliList(var1);
	}
}

// STUB: SADX 0x0068af80
void ObjectSSParasol(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, (struct CCL_INFO *)0x26ddec8, 1, 4);
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
