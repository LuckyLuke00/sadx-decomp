#include "decls.h"
extern int DAT_060eeaac;
extern int DAT_060eeac8;
extern struct NJS_POINT2 DAT_05b3e050;
extern short DAT_05b9d744;
extern unsigned char DAT_05bafb9d;
extern unsigned char DAT_05bafc18;
extern unsigned char DAT_05bafc50;
extern unsigned char DAT_05bafc96;
void FUN_007d21b0(...);

// FUNCTION: SADX 0x006b27c0
void FinalEggDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	FUN_004a0520(-1.0f, -100000.0f);
	___njFogDisable();
	___njSetTexture((struct NJS_TEXLIST *)(*(int *)((char *)DAT_060eeac8 + 0x4)));
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_ActionClip((struct NJS_ACTION *)(*(int *)((char *)DAT_060eeaac + 0x0)), var1->scl.x, 1.0f);
	ds_ActionClip((struct NJS_ACTION *)(*(int *)((char *)DAT_060eeaac + 0x78)), var1->scl.y, 1.0f);
	njPopMatrix(1);
	___njFogEnable();
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
}

// FUNCTION: SADX 0x006b2900
void ObjectMysticRuinFinalEgg(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if ((unsigned char)DAT_05b9d744 == 2)
	{
		int var2 = GetPlayerNumber();
		int var3;
		switch (var2)
		{
		case 0:
			var3 = DAT_05bafb9d;
			break;
		case 3:
			var3 = DAT_05bafc18;
			break;
		case 5:
			var3 = DAT_05bafc50;
			break;
		case 6:
			var3 = DAT_05bafc96;
			break;
		default:
			return;
		}
		if (var3 != 0)
		{
			switch (var1->mode)
			{
			case 0:
				tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
				tp->disp = FinalEggDisplayer;
				var1->mode = 1;
				break;
			case 1:
				var1->scl.x += 0.20000000298023224f;
				if (var1->scl.x >= 59.0f)
				{
					var1->scl.x = 0.0f;
					FinalEggDisplayer(tp);
					return;
				}
				break;
			}
			FinalEggDisplayer(tp);
		}
	}
}
