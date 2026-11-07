#include "decls.h"
extern struct CCL_INFO DAT_0480b368[];
extern struct obj object_cas_obj_main1f_neon_main1f_neon[];
static void End(struct task *tp);
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// GLOBAL: SADX 0x0480b3c8
static struct TEXUVINFO texuvinfo[9];

// FUNCTION: SADX 0x008769e0
static void End(struct task *tp)
{
	ObjCasino_EndTexUvInfo(&texuvinfo[0], 9);
}

// FUNCTION: SADX 0x008769f0
static void Disp(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		if (var1->smode != 0)
		{
			ObjCasino_SetTexUvInfo((struct TEXUVINFO *)((char *)&DAT_0480b368[0].angx + var1->smode * 0x3c), 3);
		}
		SetObjectTexture2(0xc);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		ds_DrawObjectClip((struct obj *)&object_cas_obj_main1f_neon_main1f_neon, 1.0f);
		njPopMatrix(1);
		if (var1->smode != 0)
		{
			ObjCasino_ResetTexUvInfo(texuvinfo, 9);
		}
	}
}

// STUB: SADX 0x00876aa0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00876b20
void ObjectCasinoMain1fNeon(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) != 0)
	{
		return;
	}
	tp->disp = Disp;
	tp->exec = Exec;
	tp->dest = End;
	var1->wtimer = 0;
	var1->smode = 0;
	ObjCasino_InitTexUvInfo(texuvinfo, 9);
	FUN_004c39c0(tp);
}
