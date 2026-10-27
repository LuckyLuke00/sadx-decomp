#include "decls.h"
extern float DAT_05b3df40;
extern int DAT_05b9d838;
extern struct obj *DAT_060eea9c;
extern int DAT_060eeaac;
void FUN_007d21b0(...);

#pragma optimize("", off)
// STUB: SADX 0x006b2450
void GrassDisplayer(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006b2500
void BigGrassDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	DAT_05b3df40 = -37952.0f;
	if (var1->flag & 0x100)
	{
		var1->flag &= 0xfeff;
		late_ActionClipEx((struct NJS_ACTION *)(*(int *)((char *)DAT_060eeaac + 0x7c)), var1->value.f, 1, 1.0f);
	}
	else
	{
		late_DrawObjectClip((struct obj *)*(int *)((char *)DAT_060eea9c + 0x18c), 1, 1.0f);
	}
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006b25c0
void ObjectMysticRuinGrass(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->disp = GrassDisplayer;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			var1->mode = 1;
			break;
		case 1:
			if (CheckCollisionP(&var1->pos, 50.0f) == 1)
			{
				var1->value.f = 0.0f;
				var1->mode = 2;
				var1->btimer = 3;
				dsPlay_oneshot_v(0x253, 0, 0, 0, var1->pos.x, var1->pos.y, var1->pos.z);
			}
			break;
		case 2:
			var1->value.f += 0.5;
			var1->flag |= 0x100;
			if (var1->value.f >= 16.0f)
			{
				var1->btimer--;
				if (var1->btimer == 0)
				{
					var1->mode = 1;
				}
				var1->value.f = 0.0f;
			}
			break;
		}
		GrassDisplayer(tp);
	}
}

// FUNCTION: SADX 0x006b26c0
void ObjectMysticRuinBigGrass(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->disp = BigGrassDisplayer;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			var1->mode = 1;
			break;
		case 1:
			if (CheckCollisionP(&var1->pos, 15.0f) == 1)
			{
				float var2;
				if (GetPlayerRunningSpeed(0, &var2) != 0)
				{
					if (var2 > 0.20000000298023224f)
					{
						var1->value.f = 0.0f;
						dsPlay_oneshot(0x255, 0, 0, 0);
						var1->mode = 2;
					}
				}
			}
			break;
		case 2:
			var1->value.f += 1.0;
			var1->flag |= 0x100;
			if (var1->value.f >= 120.0)
			{
				var1->value.f = 0.0f;
				var1->mode = 1;
			}
			break;
		}
		BigGrassDisplayer(tp);
	}
}
