#include "decls.h"
extern struct task *DAT_060cc57c;

// FUNCTION: SADX 0x007d5970
void eggmoble_dest(struct task *tp)
{
	if (tp->twp->counter.ptr != 0)
	{
		Free(tp->twp->counter.ptr);
	}
	EV_ODestruct(tp->twp);
}

// STUB: SADX 0x007d5c20
void EggmobleJetEntry(struct task *tp, struct eggmoble_effect *egg)
{
}

// STUB: SADX 0x007d61f0
void eggmoble_init(struct task *tp)
{
}

// FUNCTION: SADX 0x007d6300
void ChgEggMobleMod(signed char mode)
{
	if (DAT_060cc57c != 0)
	{
		DAT_060cc57c->twp->mode = mode;
	}
}

// FUNCTION: SADX 0x007d6320
void ChgEggMobleSMod(signed char smode)
{
	if (DAT_060cc57c != NULL)
	{
		DAT_060cc57c->twp->smode = smode;
	}
}

// FUNCTION: SADX 0x007d63b0
void eggmoble_move_rapid(float x, float y, float z, long frame)
{
	struct taskwk *var1 = DAT_060cc57c->twp;
	struct motionwk *var2 = (struct motionwk *)var1->counter.ptr;
	*(float *)((char *)var2 + 0x18) = x;
	*(float *)((char *)var2 + 0x1c) = y;
	*(float *)((char *)var2 + 0x20) = z;
	*(float *)var2 = (x - var1->pos.x) / (float)frame;
	*(float *)((char *)var2 + 4) = (y - var1->pos.y) / (float)frame;
	*(float *)((char *)var2 + 8) = (z - var1->pos.z) / (float)frame;
	*(long *)((char *)var2 + 0x24) = frame;
	*(int *)((char *)var2 + 0x28) = 0;
	var1->mode = 2;
}

// STUB: SADX 0x007d6420
void eggmoble_turn(long ax, long ay, long az, long frame, signed char efmode)
{
}

// FUNCTION: SADX 0x007d6480
void eggmoble_moveandturn(float x, float y, float z, long ax, long ay, long az, long frame, signed char efmode)
{
	struct taskwk *var1 = DAT_060cc57c->twp;
	struct motionwk *var2 = (struct motionwk *)var1->counter.ptr;
	*(float *)((char *)var2 + 0x18) = x;
	*(float *)((char *)var2 + 0x1c) = y;
	*(float *)((char *)var2 + 0x20) = z;
	*(float *)var2 = (x - var1->pos.x) / (float)frame;
	*(float *)((char *)var2 + 4) = (y - var1->pos.y) / (float)frame;
	*(float *)((char *)var2 + 8) = (z - var1->pos.z) / (float)frame;
	*(long *)((char *)var2 + 0xc) = ax / frame;
	*(long *)((char *)var2 + 0x10) = ay / frame;
	*(long *)((char *)var2 + 0x14) = az / frame;
	*(long *)((char *)var2 + 0x24) = frame;
	*(int *)((char *)var2 + 0x28) = 0;
	var1->mode = 4;
	if (efmode == 0)
	{
		if (ay > 0)
		{
			var1->smode = 2;
		}
		if (ay < 0)
		{
			var1->smode = 3;
		}
	}
}

// FUNCTION: SADX 0x007d6520
void seteggmobleparam(float updown_rat, long updown_acc)
{
	struct taskwk *var1;
	void *var2;
	var1 = DAT_060cc57c->twp;
	var2 = var1->counter.ptr;
	if (updown_rat >= 0.0f)
	{
		*(float *)((char *)var2 + 0x30) = updown_rat;
	}
	if (updown_acc >= 0)
	{
		*(int *)((char *)var2 + 0x38) = (int)updown_acc;
	}
}

// FUNCTION: SADX 0x007d6550
struct task *GetEggMobleTask()
{
	return DAT_060cc57c;
}
