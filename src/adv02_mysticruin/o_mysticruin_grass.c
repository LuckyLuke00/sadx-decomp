#include "decls.h"
void FUN_007d21b0(void *param_1);

// STUB: SADX 0x006b25c0
void ObjectMysticRuinGrass(struct task *tp)
{
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
