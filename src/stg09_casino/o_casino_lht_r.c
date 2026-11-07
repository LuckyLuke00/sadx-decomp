#include "decls.h"
extern struct obj object_cas_rt_lht_rt_lht[];
static void End(struct task *tp);
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// GLOBAL: SADX 0x0480a688
static struct TEXANIMINFO texanim[2];

// FUNCTION: SADX 0x008730a0
static void End(struct task *tp)
{
	FUN_007d21b0(&texanim[0], 2);
}

// FUNCTION: SADX 0x008730b0
static void Disp(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		if (dsCheckViewV(&var1->pos, 30.0f))
		{
			FUN_00889bd0(&texanim[var1->mode == 0], 1);
			SetObjectTexture2(0xc);
			njPushMatrix(0);
			njTranslateV(0, &var1->pos);
			if (var1->ang.z)
			{
				njRotateZ(0, (unsigned short)(short)var1->ang.z);
			}
			if (var1->ang.x)
			{
				njRotateX(0, (unsigned short)(short)var1->ang.x);
			}
			if (var1->ang.y)
			{
				njRotateY(0, (unsigned short)(short)var1->ang.y);
			}
			late_DrawObjectClip(&object_cas_rt_lht_rt_lht[0], 4, 1.0f);
			njPopMatrix(1);
			ObjCasino_ResetTexAnimInfo(&texanim[0], 2);
		}
	}
}

// STUB: SADX 0x00873190
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x008732f0
void ObjectCasinoLhtR(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) != 0)
	{
		return;
	}
	var1->wtimer = 0;
	var1->mode = 1;
	tp->disp = Disp;
	tp->exec = Exec;
	tp->dest = End;
	ObjCasino_InitTexAnimInfo(texanim, 2);
}
