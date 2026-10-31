#include "decls.h"

// GLOBAL: SADX 0x026ed260
static struct CCL_INFO object_c_info[1];

static void Exec(struct task *tp);
extern struct NJS_TEXLIST texlist_ec_ikada;
static void Disp(struct task *tp);
static long SeqCheck();
extern unsigned char DAT_05bafba3;
extern unsigned char DAT_05bafbde;
extern unsigned char DAT_05bafc1d;
extern unsigned char DAT_05bafc55;
extern unsigned char DAT_05bafc99;
extern unsigned char DAT_05bafcd4;
extern struct obj **DAT_060eea88;

// FUNCTION: SADX 0x00694840
static long SeqCheck()
{
	long var1 = GetPlayerCharacterName(0);
	switch (var1)
	{
		case 0:
			return DAT_05bafba3;
		case 2:
			return DAT_05bafbde;
		case 3:
			return DAT_05bafc1d;
		case 5:
			return DAT_05bafc55;
		case 6:
			return DAT_05bafc99;
		case 7:
			return DAT_05bafcd4;
		default:
			return 0;
	}
}

// FUNCTION: SADX 0x006948b0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_ec_ikada);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eea88 + 0x7c), 1.0f);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x00694920
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006949f0
void ObjectECIkada(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct colliwk *var2;
	struct CCL_INFO *var3;
	int var4;

	var1->mode = 0;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, object_c_info, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 30.0f);
		var2 = var1->cwp;
		var3 = var2->info;
		var4 = SeqCheck();
		if (var4 == 0)
		{
			var1->mode = 1;
			var3->attr |= 0x10;
			tp->disp = 0;
		}
		else
		{
			var1->mode = 0;
			var3->attr &= 0xffffffef;
			tp->disp = Disp;
		}
	}
	tp->exec = Exec;
}
