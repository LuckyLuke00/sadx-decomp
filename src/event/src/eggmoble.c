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

// FUNCTION: SADX 0x007d6280
void FUN_007d6280(float param_1, float param_2, float param_3, long param_4, long param_5, long param_6)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 5, eggmoble_init);
	if (var1)
	{
		var2 = var1->twp;
		var2->pos.x = param_1;
		var2->ang.x = param_4;
		var2->pos.y = param_2;
		var2->ang.y = param_5;
		var2->pos.z = param_3;
		var2->ang.z = param_6;
		var2->scl.x = 1.0f;
		DAT_060cc57c = var1;
		var2->scl.y = 1.0f;
		var2->scl.z = 1.0f;
	}
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

// FUNCTION: SADX 0x007d6420
void eggmoble_turn(long ax, long ay, long az, long frame, signed char efmode)
{
	struct taskwk *var1 = DAT_060cc57c->twp;
	struct motionwk *var2 = (struct motionwk *)var1->counter.ptr;
	*(long *)((char *)var2 + 0x24) = frame;
	*(int *)((char *)var2 + 0x28) = 0;
	*(long *)((char *)var2 + 0xc) = ax / frame;
	*(long *)((char *)var2 + 0x10) = ay / frame;
	*(long *)((char *)var2 + 0x14) = az / frame;
	var1->mode = 3;
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
