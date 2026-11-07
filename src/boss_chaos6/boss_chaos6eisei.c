#include "decls.h"
extern int DAT_060c3540[16];

// FUNCTION: SADX 0x006f9380
void objExit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	EraseDolbyCtrl(var1);
	if (var1->value.b[0] >= 0)
	{
		DAT_060c3540[var1->value.b[0]] = 0;
	}
	*(short *)(DAT_060c3540 + 7) -= 1;
	if (*(short *)(DAT_060c3540 + 7) < 0)
	{
		*(short *)(DAT_060c3540 + 7) = 0;
	}
}

// FUNCTION: SADX 0x006f95e0
void EFF_C6IceFloor_disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	SetMaterial(var1->counter.f, var1->counter.f, var1->counter.f, var1->counter.f);
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)(short)var1->ang.x);
	}
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)(short)var1->ang.y);
	}
	njRotateX(NULL, 0x4000);
	late_DrawSprite3D(&sprite_c6ice, 0, 0x22, 4);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006f96a0
void EFF_C6IceFloor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		dsPlay_timer_v(0x18e, (int)var1, 1, 0, 0xa, var1->pos.x, var1->pos.y, var1->pos.z);
		var1->counter.f += 0.012500000186264515;
		if (var1->counter.f >= 0.75f)
		{
			var1->mode = 1;
		}
		break;
	case 1:
		var1->timer.l++;
		if (var1->timer.l < 0x258)
		{
			break;
		}
		var1->mode = 2;
		EFF_C6IceFloor_disp(tp);
		return;
	case 2:
		var1->counter.f -= 0.012500000186264515;
		if (var1->counter.f <= 0.0f)
		{
			DestroyTask(tp);
			return;
		}
		break;
	}
	EFF_C6IceFloor_disp(tp);
}

// STUB: SADX 0x006f9760
void SetEFF_C6IceFloor(struct NJS_POINT3 *pos, int num)
{
}

// STUB: SADX 0x006f9850
void SlipPlayer(struct task *tp)
{
}

// STUB: SADX 0x006fa3f0
void EiseiRollCtrl(struct task *tp)
{
}
