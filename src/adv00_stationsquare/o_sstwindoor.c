#include "decls.h"

// GLOBAL: SADX 0x026de918
static struct CCL_INFO ccinfo[5];

static long SeqCheck();
void FUN_0068fd70(struct task *param_1);
static void ObjectOpen(struct task *tp);
static void ObjectMain(struct task *tp);
static void ObjectClose(struct task *tp);
extern struct NJS_ACTION action_sssikake_twindoor[];

#pragma optimize("", off)
// STUB: SADX 0x0068f9b0
static long SeqCheck()
{
	return (long)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0068fa50
void FUN_0068fa50(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_ActionClip(action_sssikake_twindoor, *(float *)((char *)var1 + 8), 1.0f);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x0068fb40
static void ObjectClose(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0068fbd0
void ObjectWait(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	FUN_0068fa50(tp);
	if (!var1->btimer)
	{
		if (CheckCollisionP(&var1->pos, 15.0f))
		{
			return;
		}
		tp->exec = ObjectClose;
		dsPlay_oneshot(0x212, 0, 0, 0);
	}
	else
	{
		var1->btimer--;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0068fc40
static void ObjectOpen(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0068fcd0
static void ObjectMain(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct CCL_INFO *var2;

	if (FUN_004c39c0(tp) != 0)
	{
		FUN_0068fa50(tp);
		return;
	}
	if (CheckRangeOut(tp) == 0)
	{
		FUN_0068fa50(tp);
		if (CheckCollisionP(&var1->pos, 15.0f))
		{
			tp->exec = ObjectOpen;
			dsPlay_oneshot(0x212, 0, 0, 0);
		}
		var2 = var1->cwp->info;
		*(int *)((char *)var2 + 4) |= 0x10;
		*(int *)((char *)var2 + 0x34) |= 0x10;
		*(int *)((char *)var2 + 0x64) &= 0xffffffef;
		*(int *)((char *)var2 + 0x94) &= 0xffffffef;
		*(int *)((char *)var2 + 0xc4) &= 0xffffffef;
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x0068fdc0
void ObjectSSTwindoor(struct task *tp)
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
			tp->exec = FUN_0068fd70;
		}
		tp->disp = FUN_0068fa50;
	}
}
