#include "decls.h"

// FUNCTION: SADX 0x006f95e0
void EFF_C6IceFloor_disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	SetMaterial(var1->counter.f, var1->counter.f, var1->counter.f, var1->counter.f);
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	njRotateX((float *)0, 0x4000);
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
