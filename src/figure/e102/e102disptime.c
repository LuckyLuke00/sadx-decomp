#include "decls.h"
extern struct NJS_SPRITE sprite_digit;
void E102AddSecTotalNew(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void AddTime(int sec);
int dsPlay_oneshot(int tone, int id, int pri, int volofs);
extern int DAT_05edc134;
extern unsigned char DAT_05cc43a1;
extern int DAT_05edc138;

// FUNCTION: SADX 0x005b9b20
void AddTimeComboAfter(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (((short)local_8->timer.w[1]) > 0)
	{
		local_8->timer.w[1]--;
	}
	else
	{
		local_8->timer.w[1] = 3;
		if (((short)local_8->timer.w[0]) > 0)
		{
			local_8->timer.w[0]--;
			AddTime(1);
			dsPlay_oneshot(4, 0, 0, 0);
		}
		if (((short)local_8->timer.w[0]) == 0)
		{
			DAT_05cc43a1 = 1;
			DestroyTask(tp);
		}
	}
}

// FUNCTION: SADX 0x005b9bc0
void DispDigitTotal(long digit, float scl, struct NJS_POINT3 *pos)
{
	long local_10l;
	float local_ci;
	float local_8g;
	float local_14;

	local_10l = digit;
	local_ci = scl * 24.0f;
	local_8g = scl * 24.0f;
	sprite_digit.p.x = pos->x;
	if (digit > 99)
	{
		sprite_digit.p.x = sprite_digit.p.x + local_ci;
	}
	else if (digit > 9)
	{
		sprite_digit.p.x = local_ci * 0.5f + sprite_digit.p.x;
	}
	sprite_digit.p.y = pos->y - local_8g * 0.30000001192092896f;
	sprite_digit.sy = scl;
	sprite_digit.sx = sprite_digit.sy;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	SetMaterial(1.0f, 1.0f, 1.0f, 0.0f);
	while (digit > 0)
	{
		local_14 = (float)local_10l + -1.0f;
		if (local_14 >= -3.0f && local_14 < 12048.0f)
		{
			local_14 = local_14 + 22048.0f;
		}
		late_DrawSprite2D(&sprite_digit, digit % 10, local_14, 0x22, 4);
		sprite_digit.p.x = sprite_digit.p.x - local_ci;
		digit = digit / 10;
	}
	sprite_digit.sy = 1.0f;
	sprite_digit.sx = sprite_digit.sy;
	SetMaterial(0.0f, 0.0f, 0.0f, 0.0f);
}

// FUNCTION: SADX 0x005b9d40
void E102AddRestTime(int add_time)
{
	struct task *local_8;

	if (DAT_05edc134 == 0)
	{
		local_8 = CreateElementalTask(2, 2, E102AddSecTotalNew);
		if (local_8 == 0)
		{
			AddTime(1);
			dsPlay_oneshot(4, 0, 0, 0);
			return;
		}
	}
	else
	{
		local_8 = (struct task *)DAT_05edc134;
	}
	local_8->twp->timer.b[1]++;
}

// FUNCTION: SADX 0x005b9db0
void E102AddRestTimeNew(struct task *atp)
{
	if (atp == 0)
	{
		if (DAT_05edc134 == 0)
		{
			atp = CreateElementalTask(2, 2, E102AddSecTotalNew);
			if (atp == 0)
			{
				AddTime(1);
				dsPlay_oneshot(4, 0, 0, 0);
				return;
			}
		}
		else
		{
			atp = (struct task *)DAT_05edc134;
		}
		if (atp->twp != 0)
		{
			atp->twp->timer.b[0]++;
		}
	}
	if (atp->twp != 0)
	{
		atp->twp->timer.b[1]++;
	}
}

// FUNCTION: SADX 0x005ba1d0
void AddTimeComboAfterDest(struct task *tp)
{
	DAT_05edc138--;
}

// STUB: SADX 0x005ba1f0
void E102AddSecTotalNewDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x005ba3b0
void E102AddSecTotalNewDest(struct task *tp)
{
	DAT_05edc134 = 0;
	DAT_05cc43a1 = 1;
	if (((signed char)tp->twp->mode) != 0x7f)
	{
		DAT_05edc138 = DAT_05edc138 - 1;
	}
}
