#include "decls.h"
static void Disp(struct task *tp);
static void Exec(struct task *tp);
static void End(struct task *tp);

// GLOBAL: SADX 0x0480a670
static struct TEXANIMINFO texanim[2];

extern struct obj object_cas_gb_lht_gb_lht[1];
void FUN_00889bd0(struct TEXANIMINFO *param_1, int param_2);

// STUB: SADX 0x00872e00
static void End(struct task *tp)
{
}

// FUNCTION: SADX 0x00872e10
static void Disp(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		if (dsCheckViewV(&var1->pos, 105.0f))
		{
			FUN_00889bd0(&texanim[var1->mode == 0], 1);
			SetObjectTexture2(0xc);
			njPushMatrix(0);
			njTranslateV(0, &var1->pos);
			if (*(int *)((char *)var1 + 0x1c))
			{
				njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x14))
			{
				njRotateX(0, (unsigned short)*(short *)((char *)var1 + 0x14));
			}
			if (*(int *)((char *)var1 + 0x18))
			{
				njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
			}
			late_DrawObjectClip(&object_cas_gb_lht_gb_lht[0], 4, 1.0f);
			njPopMatrix(1);
			ObjCasino_ResetTexAnimInfo(&texanim[0], 2);
		}
	}
}

// STUB: SADX 0x00872ef0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00873050
void ObjectCasinoLhtG(struct task *tp)
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
