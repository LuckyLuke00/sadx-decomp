#include "decls.h"
extern short DAT_05b9d744;
extern unsigned char DAT_05bafb9d;
extern unsigned char DAT_05bafc18;
extern unsigned char DAT_05bafc50;
extern unsigned char DAT_05bafc96;
void FUN_007d21b0(void *param_1);

// STUB: SADX 0x006b27c0
void FinalEggDisplayer(struct task *tp)
{
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
