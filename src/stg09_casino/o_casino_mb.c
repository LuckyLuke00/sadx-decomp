#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);
extern struct CCL_INFO object_c_info[];
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_05b39be8;
static void End(struct task *tp);

// FUNCTION: SADX 0x008777b0
static void End(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (FUN_004c39c0(tp) == 0)
	{
		if (var1->value.w[0] == (DAT_05b9d724 << 8 | DAT_05b9d744))
		{
			DAT_05b39be8 = var1->smode;
		}
	}
}

// FUNCTION: SADX 0x008777f0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 490010.0f) == 0)
	{
		if (dsCheckViewV(&var1->pos, 40.0f))
		{
			SetObjectTexture2(0xc);
			njPushMatrix(0);
			njTranslateV(0, &var1->pos);
			if (var1->ang.y)
			{
				njRotateY(0, (Uint16)var1->ang.y);
			}
			ds_DrawObjectClip(object_cas_obj_mball_mball, 1.0f);
			njPopMatrix(1);
		}
	}
}

#pragma optimize("", off)
// STUB: SADX 0x00877880
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00877920
void ObjectCasinoMBall(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 490010.0f) == 0)
	{
		tp->disp = Disp;
		tp->exec = Exec;
		tp->dest = End;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_c_info[0], 1, 4);
		}
		var1->value.w[0] = (DAT_05b9d724 << 8) | DAT_05b9d744;
		var1->smode = (char)DAT_05b39be8;
	}
}
