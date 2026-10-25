#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern struct CCL_INFO mi_flag_colli_info[];
extern void FUN_007d21b0(void *param_1);

// FUNCTION: SADX 0x0049c7d0
static void Disp(struct task *tp)
{
	struct taskwk *var2 = tp->twp;
	unsigned char *var3 = *(unsigned char **)((char *)tp->ocp + 0x10);
	___njSetTexture(&texlist_kariobj);
	njPushMatrix(0);
	matlist_mission_item_flag01_flag02[0].attr_texId = (unsigned long)((int)var3[8] % 7);
	matlist_mi_flag[0].attr_texId = matlist_mission_item_flag01_flag02[0].attr_texId;
	njTranslateV(0, &var2->pos);
	if (var2->ang.y != 0)
	{
		njRotateY(0, (unsigned short)var2->ang.y);
	}
	njScaleV(0, &var2->scl);
	___dsDrawObject((struct obj *)&object_mi_flag);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x0049c860
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0049ca00
void ObjectMiFlag(struct task *tp)
{
	if (IsMissionAppear(tp))
	{
		CCL_Init(tp, mi_flag_colli_info, 1, 4);
		tp->exec = Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Disp;
	}
}
