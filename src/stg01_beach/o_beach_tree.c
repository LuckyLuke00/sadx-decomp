#include "decls.h"

// GLOBAL: SADX 0x03a0ca38
static struct CCL_INFO object_c_info[4];

// FUNCTION: SADX 0x007ffe70
void Draw3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrixEx();
		njTranslateEx(&var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		late_DrawObjectClipEx(&object_seaobj_yashi04_yashi04[0], 1, 1.0f);
		njPopMatrixEx();
	}
}

// FUNCTION: SADX 0x00800130
void ObjectBeachYasi3(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut_L(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			if (FUN_004c39c0(tp) == 0)
			{
				CCL_Init(tp, &object_c_info[3], 1, 4);
			}
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = Draw3;
			var1->mode = 1;
			break;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				EntryColliList(var1);
				ObjectSetupInput(var1, NULL);
			}
			Draw3(tp);
			break;
		case 2:
			DeadOut(tp);
			break;
		}
	}
}
