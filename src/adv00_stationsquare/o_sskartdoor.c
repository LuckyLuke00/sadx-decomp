#include "decls.h"
static long SeqCheck();

// GLOBAL: SADX 0x026dec50
static struct CCL_INFO ccinfo[5];

static void ObjectMain(struct task *tp);
extern unsigned char DAT_05bafb8a;
extern unsigned char DAT_05bafbc8;
extern unsigned char DAT_05bafc06;
extern unsigned char DAT_05bafc45;
extern unsigned char DAT_05bafc84;
extern unsigned char DAT_05bafcc3;
extern struct NJS_ACTION action_sssikake_kartdoor[1];

// FUNCTION: SADX 0x00690830
static long SeqCheck()
{
	long var1 = GetPlayerCharacterName(0);
	switch (var1)
	{
		case 0:
			return DAT_05bafb8a;
		case 2:
			return DAT_05bafbc8;
		case 3:
			return DAT_05bafc06;
		case 5:
			return DAT_05bafc45;
		case 6:
			return DAT_05bafc84;
		case 7:
			return DAT_05bafcc3;
		default:
			return 0;
	}
}

// FUNCTION: SADX 0x006908a0
void FUN_006908a0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	SetObjectTexture();
	ds_ActionClip((struct NJS_ACTION *)&action_sssikake_kartdoor, *(float *)((char *)var1 + 8), 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x00690910
void ObjectColliSet(struct taskwk *twp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00690990
void ObjectClose(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00690b20
static void ObjectMain(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00690bc0
void FUN_00690bc0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct CCL_INFO *var2;

	if (CheckRangeOut(param_1) == 0)
	{
		if (FUN_004c39c0(param_1) == 0)
		{
			if (SeqCheck() != 0)
			{
				param_1->exec = ObjectMain;
			}
			var2 = var1->cwp->info;
			*(int *)((char *)var2 + 4) |= 0x10;
			*(int *)((char *)var2 + 0x34) |= 0x10;
			*(int *)((char *)var2 + 0x64) &= 0xffffffef;
			*(int *)((char *)var2 + 0x94) &= 0xffffffef;
			*(int *)((char *)var2 + 0xc4) &= 0xffffffef;
			EntryColliList(var1);
		}
		FUN_006908a0(param_1);
	}
}

// FUNCTION: SADX 0x00690c30
void ObjectSSKartdoor(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, ccinfo, 5, 4);
		if (SeqCheck() != 0)
		{
			tp->exec = ObjectMain;
		}
		else
		{
			tp->exec = FUN_00690bc0;
		}
		tp->disp = FUN_006908a0;
	}
}
