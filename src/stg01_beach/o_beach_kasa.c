#include "decls.h"
static void Exec(struct task *tp);

// GLOBAL: SADX 0x03a0c200
static struct CCL_INFO object_c_info[2];

static void Disp(struct task *tp);
extern struct obj object_seaobj_parasol03_parasol03[];
extern int DAT_05b9d838;

// FUNCTION: SADX 0x007f9270
static void Disp(struct task *tp)
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawObjectClipEx(object_seaobj_parasol03_parasol03, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007f92e0
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut_L(tp) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			EntryColliList(var1);
		}
		Disp(tp);
	}
}

// FUNCTION: SADX 0x007f9320
void ObjectBeachKasa(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->ang.x = 0;
	var1->ang.z = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 2, 4);
	}
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
